#include "Include.h"

//变量声明
uint8   guc_DyUart4Over;        //模拟串口超时保护
/*=========================================================================================\n
* @function_name: Init_Uart4
* @function_file: Uart4.c
* @描述: uart4的初始化
* 
* 
* @参数: 
* @param:ucBode  波特率  0-600  1-1200 2-2400 3-4800 4-9600
* @返回: 
* @作者:   lwb (2012-05-31)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Init_Uart4(uint8 ucBode)
{

    if(ucBode>=5)
    {
        ucBode=2;                           //默认2400
    }

    TMOD4 = 0x20;                               // 8-bit counter with auto-reload
    TCON4 = BaudRateTable[ucBode].Type;          //时钟选择CLK  clear SMOD  SET  T1M,TR1
    TL41  = TH41 = BaudRateTable[ucBode].THValue;    //波特率设置
    SCON4 = 0xD0;                                 //数据位9位,8位数据位+1校验位

    P2OE &= ~BIT1;                      //Uart4发送口输出允许
    P2IE &= ~BIT1;                      //Uart4发送口输入禁止
    P2OE |= BIT0;                       //Uart4接收口输出禁止
    P2IE |= BIT0;                       //Uart4接收口输入允许
    P20FS=2;                            //P2.0配置成RXD
    P21FS=2;                            //P2.1配置成TXD
    
    ExInt2IE|=BIT2;
    ExInt2IE|=BIT3;
    EIE|=BIT0;
#ifdef RS485_TWOLINE
    Uart4_CtrIoIdle();
#else
    Uart4_RevEn();
#endif
}

/*=========================================================================================\n
* @function_name: Uart4_Dy10ms
* @function_file: Uart4.c
* @描述: 模拟串口的超时保护
*       为防止锁死，定时保护，当没有任何数据发送和接收的时候，初始化
* @参数:
* @返回:
* @作者:   lwb (2012-03-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Uart4_Dy10ms(void)
{
    guc_DyUart4Over--;
    if(0x00== guc_DyUart4Over)
    {
        Init_Uart4(guc_485Bode);        // 初始化模拟串口
        ComBom_Init(ComIndex_Uart4);    //将uart4 端口对应的 COM初始化
    }

    if(guc_BodeDely>0)                  //波特率切换
    {
        guc_BodeDely--;
        if(guc_BodeDely==0)
        {
            gui_RefreshEvent |= flgEtPara_Bode;
        }
    }
}
/*=========================================================================================\n
* @function_name: Uart4_Receive
* @function_file: Uart4.c
* @描述: UART4接收,在中断中调用该函数
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Uart4_Receive(void)
{
    uint8 temp,temp1;
    guc_DyUart4Over = Const_DyUart4Over;//端口超时保护
    //这里可以做奇偶校验判断
    ACC=SBUF4;                          //ACC 奇校验
    temp=P;
    temp1=(SCON4>>2)&BIT0;              //偶校验

    if(temp!=temp1)                     //奇偶校验位不正确
    {
        return;
    }

    //处于空闲状态或已经处于uart接收状态
    gs_ComGroup[ComIndex_Uart4].ucPort   = Port_Uart4;

    gs_ComGroup[ComIndex_Uart4].ucRecvTmr = Const_DyRvPack;     //设置数据包接收超时时间

    if(gs_ComGroup[ComIndex_Uart4].ucStt == ComStt_Idle)        //当前是空闲的状态的话，判断是否是帧头68
    {
        if(SBUF4==COMHEAD)               //接受到起始字节
        {
            gs_ComGroup[ComIndex_Uart4].ucStt = ComStt_Recv;
        }
    }

    if(gs_ComGroup[ComIndex_Uart4].ucStt == ComStt_Recv)            //这个判断是防止发送的时候有接收中断进入的可能
    {
        if(gs_ComGroup[ComIndex_Uart4].ucLen < Const_MaxBufLen)     //判断 com中的buf是否溢出
        {
            //防止缓存溢出
            gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucLen++] = SBUF4;//数据存入缓冲区，指针加加

            if(gs_ComGroup[ComIndex_Uart4].ucLen>COMINITLEN)
            {
                if(gs_ComGroup[ComIndex_Uart4].ucBuf[7]!=COMHEAD)           //如果第7个不是68返回错误
                {
                    gs_ComGroup[ComIndex_Uart4].ucStt=ComStt_Idle;
                }else if(gs_ComGroup[ComIndex_Uart4].ucLen>=(gs_ComGroup[ComIndex_Uart4].ucBuf[9]+COMINITLEN+2))   //长度符合要求
                {
                    if(SBUF4==COMTAIL)
                    {
                        guc_ComSendDy=3;                                        //延时30ms发送
                        gs_ComGroup[ComIndex_Uart4].ucStt=ComStt_WaitProc;
                        gui_SystemEvent |= flgEtGlb_NeedPrtclChk;               // 设置标志
                        gs_ComGroup[ComIndex_Uart4].ucRecvTmr=0;
                        //关闭接收
                    }
                }
            }
        }
    }
}
/*=========================================================================================\n
* @function_name: Uart4_Transmit
* @function_file: Uart4.c
* @描述: UART4发送,中断中调用
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Uart4_Transmit(void)
{
    guc_DyUart4Over = Const_DyUart4Over;//端口超时保护

    if(gs_ComGroup[ComIndex_Uart4].ucPort   == Port_Uart4)
    {   //处于空闲状态或已经处于uart接收状态
        if(gs_ComGroup[ComIndex_Uart4].ucStt == ComStt_Send)
        {
            if(gs_ComGroup[ComIndex_Uart4].ucPos >= gs_ComGroup[ComIndex_Uart4].ucLen)
            {   //发送完毕,初始化通讯控制状态
            #ifdef RS485_TWOLINE
                Uart4_CtrIoIdle();
            #else
                Uart4_RevEn();
            #endif
                ComBom_Init(ComIndex_Uart4);//将uart4 端口对应的 COM初始化
            }else
            {
//              if(gs_ComGroup[ComIndex_Uart4].ucFrmHeadCnt<4)
//              {
//                  SCON4|=(BIT3);
//                  SBUF4=0xfe;
//                  gs_ComGroup[ComIndex_Uart4].ucFrmHeadCnt++;
//              }else
                {
                    //这里可以做奇偶校验运算
                    ACC = gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucPos]; //计算校验位
                    if(P==0)                                        //校验位
                    {
                        SCON4&=(~BIT3);
                    }
                    else
                    {
                        SCON4|=(BIT3);
                    }
                    SBUF4 = gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucPos++]; 
                }
            #ifdef RS485_TWOLINE
                Uart4_CtrIoIdle();
            #else
                Uart4_SendEn();//控制端口设置为发送模式（三线制通讯使用）  //还有未发送数据则写入外设发送缓存
            #endif

            }
        }else
        {   //如果在发送中断标记中，进入但是状态不正确，则初始化
            ComBom_Init(ComIndex_Uart4);//将uart4 端口对应的 COM初始化
        #ifdef RS485_TWOLINE
            Uart4_CtrIoIdle();
        #else
            Uart4_RevEn();
        #endif
        }
    }
}

