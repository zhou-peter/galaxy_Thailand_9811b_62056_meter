#define AP_CORETAB_EXT
#include "Include.h"

/*=========================================================================================\n
* @function_name: FunList
* @function_file: ComCoretab.c
* @描述: 定义特殊处理函数，往这个表里面添加函数只能在末尾添加，请不要在中间添加，否则就乱了
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-17)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
const PFUNC code FunList[] = 
{
    FunToBeDef,                     //0x00
    FunToBeDef,//ComReadRunCode,                 //0x01 读取运行状态字
    FunToBeDef,//ReadAccuEgy,                    //0x02 读取周期电量
    FunToBeDef,//ReadCurEgy,                     //0x03 读取当前的电量
    FunToBeDef,//ReadHisEgy,                     //0x04 读取历史的电量
    FunToBeDef,//ComRWE2Para,                    //0x05 读取E2参数
    FunToBeDef,//ComMeterConst,                  //0x06 读取电表常数 
    FunToBeDef,//ComRdEvCnt,                     //0x07 读取事件记录次数
    FunToBeDef,//RwGGJR,                         //0x08 公共假日读写
    FunToBeDef,//ReadJL,                         //0x09 读取编程记录（电表清零、开表盖..）
    FunToBeDef,//RwSqSd,                         //0x0A 读写日时段时区等
    FunToBeDef,//RwDjData,                       //0x0B 读取冻结数据
    FunToBeDef,//RwLcdData,                      //0x0C 读写显示项
    FunToBeDef,//RwSysTime,                      //0x0D 读写系统时间
    RwRamE2,                                     //0x0E 直接读写E2和Ram
    FunToBeDef,//ReadZHLYEgy,                    //0x0F 读取组合累用电量
    ReadVar,                                     //0x10 读取表里瞬时值
#ifdef LOADCURVE
    FunToBeDef,//ReadCurveJl,                    //0x11 负荷记录
#else
    FunToBeDef,                     //0x11  
#endif
    ReadSwVersion,                  //0x12 读取版本号
    FunToBeDef,//ReadEnyD0Block,                 //0x13 读取电量分费率数据块
    FunToBeDef,//WrPassWord,                     //0x14 写普通密码
    FunToBeDef,//IrShowLcd,                      //0x15 
    FunToBeDef,//ReadHisJSTime,                  //0x16  历史结算时间
    FunToBeDef,//Report,                         //0x17  主动上报
#ifdef SQSDPRLOG
    FunToBeDef,//ReadRSDLogItem,                 //0x18 日时段后续帧读取数据
    FunToBeDef,//ReadSQLogItem,                  //0x19 时区后续帧读取数据
#endif
};
//下面的数据标识必须从小到大排列

/*=========================================================================================\n
 核心表0 主要是电量的数据
===========================================================================================*/
//const S_CORETAB code gs_CoreTab0[] = 
//{
////  ID              Atb LEN D1  D0   FUNID   ADDR
//    {0x00000000,    0,  4,  4,  0,  0x03,   0,              0,}, //（当前）组合有功总电能
//    {0x00000001,    0,  4,  4,  11, 0x04,   EEP_EPHIS,      0,}, // 历史组合有功总电能
//    {0x000000ff,    0,  52, 4,  0,  0x13,   0,              0,}, // 总电量数据块当前+历史 
//    {0x00010000,    0,  4,  4,  0,  0x03,   0,              0,}, //（当前）正向有功总电能
//    {0x00010001,    0,  4,  4,  11, 0x04,   EEP_EPHIS + 20, 0,}, // 历史正向有功总电能
//    {0x000100ff,    0,  52, 4,  0,  0x13,   20,             0,}, // 总电量数据块当前+历史 
//    {0x00020000,    0,  4,  4,  0,  0x03,   0,              0,}, //（当前）反向有功总电能
//    {0x00020001,    0,  4,  4,  11, 0x04,   EEP_EPHIS + 40, 0,}, // 历史反向有功总电能
//    {0x000200ff,    0,  52, 4,  0,  0x13,   40,             0,}, // 总电量数据块当前+历史 
//
//    {0x000B0000,    0,  4,  0,  0,  0x02,   0,              0x00,}, // 当前月度组合有功总累计用电量
//    {0x000B0001,    0,  4,  0,  0,  0x02,   0,              0x01,}, // 上1月度组合有功总累计用电量
//
//    {0x000C0000,    0,  4,  0,  0,  0x0F,   0,              0x00,}, // 当前月度组合有功总累计用电量
//    {0x000C0001,    0,  4,  0,  0,  0x0F,   0,              0x01,}, // 上1月度组合有功总累计用电量
////  {0x000D0000,    0,  4,  0,  0,  0x02,   0,              0x10,}, // 当前年度组合有功总累计用电量
////  {0x000D0001,    0,  4,  0,  6,  0x02,   0,              0x11,}, // 历史年度组合有功总累计用电量
//    {0x00FE0001,    0,  4,  4,  11, 0x16,   0,              0,   }, // 历史结算时间
//    {0x00FE00ff,    0,  52, 4,  0,  0x16,   0,              0,   }, // 上一次及12次结算时间块
//};
 
/*=========================================================================================\n
 核心表2，主要是瞬时值数据
===========================================================================================*/
const S_CORETAB code gs_CoreTab2[] =
{

    //  ID              Atb         LEN D1  D0      FUNID   ADDR

    {0x02010000,  Data_BCD,     2,  0,  0,      0x10,   0,      0,      },//电压数据块查找，数据标识相当于0x0201FF00
    {0x02010100,  Data_BCD,     2,  0,  0,      0x10,   0,      0,      },//A相电压
//  {0x0201FF00,  Data_BCD,     6,  0,  0,      0x10,   0,      1,      },//电压数据块

    {0x02020000,  Data_BCD,     3,  0,  0,      0x10,   0,      2,      },//电流数据块查找，数据标识相当于0x0202FF00
    {0x02020100,  Data_BCD,     3,  0,  0,      0x10,   0,      2,      },//A相电流
//  {0x0202FF00,  Data_BCD,     9,  0,  0,      0x10,   0,      3,      },//电流数据块

    {0x02030000,  Data_BCD,     3,  0,  0,      0x10,   0,      5,      },//瞬时总有功功率
    {0x02030100,  Data_BCD,     3,  0,  0,      0x10,   0,      5,      },//瞬时A相功功率
//  {0x0203FF00,  Data_BCD,     12, 0,  0,      0x10,   0,      6,      },//功率数据块


//    {0x02060000,  Data_BCD,     2,  0,  0,      0x10,   0,      8,      },//总功率因数
//    {0x02060100,  Data_BCD,     2,  0,  0,      0x10,   0,      8,      },//A项功率因数
////  {0x0206FF00,  Data_BCD,     8,  0,  0,      0x10,   0,      9,      },//A项功率因数
//
//
////  {0x02800001,  Data_BCD,     3,  0,  0,      0x10,   0,      4,      },//零线电流
//    {0x02800002,  Data_BCD,     2,  0,  0,      0x10,   0,      7,      },//电网频率
//    {0x02800007,  Data_BCD,     2,  0,  0,      0x10,   0,      10,     },//表内温度
//    {0x02800008,  Data_BCD,     2,  0,  0,      0x10,   0,      11,     },//时钟电池电压(内部)
//    {0x0280000A,  Data_BCD,     4,  0,  0,      0x10,   0,      12,     },//内部电池工作时间
};
/*=========================================================================================\n
核心表3，主要是编程记录
===========================================================================================*/
//const S_CORETAB code gs_CoreTab3[] = 
//{
//    //  ID              Atb             LEN D1  D0      FUNID   ADDR
//    {0x03110000, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_DDETNO,     0,              },//掉电总次数
//    {0x03110001, Data_RO,               12, 0,  9,  0x09,   DDJLID,         EEP_DDETNO,     },//掉电发生时刻，结束时刻
//    {0x03300000, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_BCETNO,     0,              },//编程总次数
//    {0x03300001, Data_RO,               50, 0,  9,  0x09,   BCJLID,         EEP_BCETNO,     },//编程记录(上1次~上10次)
//    {0x03300100, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_DBQLETNO,   0,              },//电表清零总次数
//    {0x03300101, Data_RO,               18, 0,  9,  0x09,   DBQLJLID,       EEP_DBQLETNO,   },//电表清零记录(上1次~上10次)
//    {0x03300300, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_SJQLETNO,   0,              },//事件清零总次数(包括总清及分项清)
//    {0x03300301, Data_RO,               14, 0,  9,  0x09,   SJQLJLID,       EEP_SJQLETNO,   },//事件清零记录(上1次~上10次)
//    {0x03300400, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_JSETNO,     0,              },//校时总次数
//    {0x03300401, Data_RO,               16, 0,  9,  0x09,   JSJLID,         EEP_JSETNO,     },//校时记录(上1次~上10次)
//#ifdef SQSDPRLOG
//    {0x03300500, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_RSDXGNO,    0,              },//时段表编程总次数
//    {0x03300501, Data_RO,               178,0,  9,  0x18,   0,              0,              },//时段表编程记录(上1次~上10次)
//    {0x03300600, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_SQXGNO,     0,              },//时区表编程总次数
//    {0x03300601, Data_RO,               94, 0,  9,  0x19,   0,              0,              },//时区表编程记录(上1次~上10次)
//#endif
//#ifdef ZXRPRLOG
//    {0x03300700, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_ZXRXGNO,    0,              },//周休日编程总次数
//    {0x03300701, Data_RO,               11, 0,  9,  0X09,   ZXRJLID,        EEP_ZXRXGNO,    },//周休日编程记录(上1次~上10次)
//#endif    
//#ifdef YGZHZPRLOG
//    {0x03300900, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_YGZHETNO,   0,              },//有功组合方式字编程总次数
//    {0x03300901, Data_RO,               11, 0,  9,  0x09,   YGZHJLID,       EEP_YGZHETNO,   },//有功组合方式字编程记录(上1次~上10次)
//#endif
//#ifdef JSRPRLOG
//    {0x03300C00, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_JSRETNO,    0,              },//结算日编程次数
//    {0x03300C01, Data_RO,               16, 0,  9,  0x09,   JSRJLID,        EEP_JSRETNO,    },//结算日编程记录(上1次~上10次)
//#endif
//    {0x03300D00, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_KBGETNO,    0,              },//开表盖总次数
//    {0x03300D01, Data_RO,               28, 0,  9,  0x09,   KBGJLID,        EEP_KBGETNO,    },//开表盖记录(上1次~上10次)
//    {0x03370000, Data_BCD | Data_RO,    3,  0,  0,  0x07,   EEP_DYYCNO,     0,              },//电源异常总次数
//    {0x03370001, Data_RO,               20, 0,  9,  0x09,   DYGZJLID,       EEP_DYYCNO,     },//电源异记录(上1次~上10次)
//};


   
    
/*******************************************************************************
**核心表4，主要是表计的一些参数
*******************************************************************************/
//const S_CORETAB code gs_CoreTab4[] = 
//{
//    //  ID              Atb                 LEN     D1  D0  FUNID   ADDR
//    {0x04000101,    Data_RF,                4,      0,  0,  0x0D,   EEP_DATETIME,           0,      },//日期及星期(其中0代表星期天)
//    {0x04000102,    Data_RF,                3,      0,  0,  0x0D,   EEP_DATETIME + 4,       0,      },//时间
//
//
//    {0x04000105,    Data_Factor,            2,      0,  0,  0x05,   EEP_JBMCKD,             0,      },//校表脉冲宽度
//    {0x04000106,    Data_RF,                5,      0,  0,  0x05,   EEP_SQQHTM,             1,      },//两套时区表切换时间//费率刷新
//    {0x04000107,    Data_RF,                5,      0,  0,  0x05,   EEP_RSDQHTM,            1,      },//两套日时段表切换时间
//    {0x0400010C,    Data_RF,                7,      0,  0,  0x0D,   EEP_DATETIME ,          0,      },//日期,时间
//    {0x04000201,    Data_RF | Data_BCD,     1,      0,  0,  0x05,   EEP_SQCNT,              2,      },//年时区数p≤14
//    {0x04000202,    Data_RF | Data_BCD,     1,      0,  0,  0x05,   EEP_RSDCNT,             3,      },//日时段表数q≤8
//    {0x04000203,    Data_RF | Data_BCD,     1,      0,  0,  0x05,   EEP_FSDCNT,             4,      },//日时段数(每日切换数) m≤14
//    {0x04000204,    Data_RF | Data_BCD,     1,      0,  0,  0x05,   EEP_FEECNT,             5,      },//费率数k≤63
//    {0x04000205,    Data_RF | Data_BCD,     2,      0,  0,  0x05,   EEP_JRCNT,              6,      },//公共假日数n≤254
//    {0x04000301,    Data_RF | Data_BCD,     1,      0,  0,  0x05,   EEP_MAX_LX_NUM,         7,      },//自动循环显示屏数
//    {0x04000302,    Data_RF | Data_BCD,     1,      0,  0,  0x05,   EEP_LXTM,               8,      },//每屏显示时间
//    {0x04000303,    Data_RF | Data_BCD,     1,      0,  0,  0x05,   EEP_EDEC,               9,      },//显示电能小数位数
//    {0x04000304,    Data_RF | Data_BCD,     1,      0,  0,  0x05,   EEP_PDEC,               10,     },//显示功率(最大需量)小数位数
//    {0x04000305,    Data_RF | Data_BCD,     1,      0,  0,  0x05,   EEP_MAX_JX_NUM,         11,     },//按键循环显示屏数
//    {0x04000308,    Data_RF | Data_BCD,     1,      0,  0,  0x05,   EEP_FULLSHOWTM,         28,     },//上电全显时间
//    
//    {0x04000401,    0,                      6,      0,  0,  0x05,   EEP_COMADD,             26,     },//通信地址
//    {0x04000402,    0,                      6,      0,  0,  0x05,   EEP_METERNO,            12,     },//表号
//    {0x04000403,    0,                      32,     0,  0,  0x05,   EEP_ASSETNO,            0,      },//资产管理编码(ASCII码)
//    {0x04000404,    Data_Factor,            6,      0,  0,  0x05,   EEP_STANDUN,            0,      },//额定电压(ASCII码)
//    {0x04000405,    Data_Factor,            6,      0,  0,  0x05,   EEP_STANDIN,            0,      },//额定电流/基本电流(ASCII码)
//    {0x04000406,    Data_Factor,            6,      0,  0,  0x05,   EEP_MAXIN,              0,      },//最大电流(ASCII码)
//    {0x04000407,    Data_Factor,            4,      0,  0,  0x05,   EEP_YGACCURACY,         0,      },//有功准确度等级(ASCII码)
//
//    {0x04000409,    Data_RO|Data_BCD,       3,      0,  0,  0x06,   EEP_JBBCS,              0,      },//电表有功常数
//    {0x0400040B,    Data_Factor,            10,     0,  0,  0x05,   EEP_METERMODEL,         0,      },//电表型号(ASCII码)
//    {0x0400040C,    Data_Factor,            10,     0,  0,  0x05,   EEP_PDATE,              0,      },//生产日期(ASCII码)
//    {0x0400040D,    Data_Factor,            16,     0,  0,  0x05,   EEP_PROTOCOLNO,         0,      },//协议版本号(ASCII码)
//    {0x0400040E,    0,                      6,      0,  0,  0x05,   EEP_KHBH,               0,      },//客户编号
//    {0x0400040F,    0,                      11,     0,  0,  0x05,   EEP_DBWZXX,             0,      },//电表位置信息
//    
//    {0x04000501,    Data_RO,                2,      0,  6,  0x01,   0,                      0,      },//电表运行状态字1
//    {0x040005FF,    Data_RO,                14,     0,  0,  0x01,   0,                      0,      },//电表运行状态字集抄
//
//    {0x04000601,    Data_RF,                1,      0,  0,  0x05,   EEP_YGCALC,             13,     },//有功组合方式字
//    {0x04000701,    Data_RF,                1,      0,  0,  0x05,   EEP_IARBDM,             14,     },//调制型红外光口通信速率特征字
//    {0x04000703,    Data_RF,                1,      0,  0,  0x05,   EEP_UARTBDM,            15,     },//通信口1通信速率特征字
//    {0x04000705,    Data_RF,                1,      0,  0,  0x05,   0,                              },//通信口3通信速率特征字
//    {0x04000801,    Data_RF,                1,      0,  0,  0x05,   EEP_SZX,                16,     },//周休日特征字
//    {0x04000802,    Data_RF,                1,      0,  0,  0x05,   EEP_ZXSD,               17,     },//周休日采用的日时段表号
//
//    {0x04000901,    Data_RF,                1,      0,  0,  0x05,   EEP_FHJLMSZ,            29,     },//负荷记录模式字
//    {0x04000902,    0,                      1,      0,  0,  0x05,   EEP_DSFREEZ,            23,     },//定时冻结数据模式字
//    {0x04000903,    0,                      1,      0,  0,  0x05,   EEP_YDFREEZ,            23,     },//瞬时冻结数据模式字
//    {0x04000904,    0,                      1,      0,  0,  0x05,   EEP_SSFREEZ,            23,     },//约定冻结数据模式字
//    {0x04000905,    0,                      1,      0,  0,  0x05,   EEP_ZDFREEZ,            24,     },//整点冻结数据模式字
//    {0x04000906,    0,                      1,      0,  0,  0x05,   EEP_RFREEZ,             23,     },//日冻结数据模式字
//    {0x04000A01,    Data_RF,                4,      0,  0,  0x05,   EEP_FHJLTIME,           29,     },//负荷记录起始时间
//    {0x04000A02,    Data_BCD | Data_RF,     2,      0,  0,  0x05,   EEP_FHJL1JG,            29,     },//第1类负荷记录间隔时间
//    {0x04000A03,    Data_BCD | Data_RF,     2,      0,  0,  0x05,   EEP_FHJL2JG,            29,     },//第2类负荷记录间隔时间
//    {0x04000A04,    Data_BCD | Data_RF,     2,      0,  0,  0x05,   EEP_FHJL3JG,            29,     },//第3类负荷记录间隔时间
//    {0x04000A05,    Data_BCD | Data_RF,     2,      0,  0,  0x05,   EEP_FHJL4JG,            29,     },//第4类负荷记录间隔时间
//    {0x04000B01,    0,                      2,      0,  0,  0x05,   EEP_CBR1,               18,     },//每月第1结算日
//    {0x04000B02,    0,                      2,      0,  0,  0x05,   EEP_CBR2,               18,     },//每月第2结算日
//    {0x04000B03,    0,                      2,      0,  0,  0x05,   EEP_CBR3,               18,     },//每月第3结算日
//    {0x04000C01,    Data_WO,                16,     0,  9,  0x14,   EEP_645PASSWD1,         0,      },//0级密码
//    {0x04001101,    Data_RF,                1,      0,  0,  0x05,   EEP_DBYXTZZ,            31,     },//电表运行特征字
//    {0x04001104,    Data_RF,                6,      0,  0,  0x05,   EEP_ZDSBMSZ,            27,     },//主动上报模式字
//    {0x04001201,    0,                      5,      0,  0,  0x05,   EEP_ZDFREEZTM,          25,     },//整点冻结起始时间
//    {0x04001202,    Data_BCD,               1,      0,  0,  0x05,   EEP_ZDTMJG,             19,     },//整点冻结时间间隔
//    {0x04001203,    0,                      2,      0,  0,  0x05,   EEP_RFREEZTM,           20,     },//日冻结时间
//    {0x04001204,    Data_RO,                4,      0,  0,  0x05,   EEP_DSFRZ,              0,      },//定时冻结时间
//    {0x04001501,    Data_RO,                10,     0,  0,  0x17,   0,                      0,      },//主动上报状态字
//    
//    {0x04010000,    Data_BCD,               42,     0,  0,  0x0A,   EEP_1SQ,                0x01,   },//第一套时区表数据  这里不管是时区表还是时段表，首地址都是从时区表开始算起
//    {0x04010001,    Data_BCD,               42,     0,  8,  0x0A,   EEP_1SQ,                0x02,   },//第一套第1日时段表数据
//    {0x04020000,    Data_BCD,               42,     0,  0,  0x0A,   EEP_2SQ,                0x01,   },//第二套时区表数据
//    {0x04020001,    Data_BCD,               42,     0,  8,  0x0A,   EEP_2SQ,                0x02,   },//第二套第1日时段表数据
//    {0x04030001,    Data_BCD,               4,      0,  59, 0x08,   EEP_JRS,                22,     },//第1公共假日日期及日时段表号
//    {0x04040101,    0,                      5,      0,  98, 0x0C,   EEP_LXTABLE,            0,      },//自动循环显示第1屏显示数据项
//    {0x04040201,    0,                      5,      0,  98, 0x0C,   EEP_JXTABLE,            0,      },//按键循环显示第1屏显示数据项
//    {0x04040300,    Data_RO,                5,      0,  0,  0x15,   0,                      0,      },//红外查看液晶
////  {0x04091001,    Data_RF,                3,      0,  0,  0x05,   EEP_PDIRGATE,           30,     },//功率反向事件有功功率触发下限
////  {0x04091002,    Data_RF,                1,      0,  0,  0x05,   EEP_PDIRTIME,           30,     },//功率反向事件判定延时时间
//    {0x04800001,    Data_Factor,            32,     0,  0,  0x05,   EEP_CJRJBB,             0,      },//厂家软件版本号(ASCII码)
//    {0x04800002,    Data_Factor,            32,     0,  0,  0x05,   EEP_CJYJBB,             0,      },//厂家硬件版本号(ASCII码)
//    {0x04800003,    Data_Factor,            32,     0,  0,  0x05,   EEP_CJBH,               0,      },//厂家编号(ASCII码)
//    {0x04800004,    Data_Factor,            8,      0,  0,  0x05,   EEP_SWBAKNUM,           0,      },//软件备案号
//    
//};


/*******************************************************************************
**核心表5，主要是有关冻结的一些数据
*******************************************************************************/
//const   S_CORETAB code gs_CoreTab5[] = 
//{
//
//    //  ID              Atb     LEN     D1  D0  FUNID   ADDR
//    {0x05000001,    Data_RO,    49,     2,  59, 0x0B,   DSDJID,     0, },//（上1次）定时冻结时间
//    {0x05001001,    Data_RO,    49,     0,  59, 0x0B,   DSDJID,     0, },//（上1次）定时冻结变量数据
//    {0x05010001,    Data_RO,    49,     2,  2,  0x0B,   SSDJID,     1, },//（上1次）瞬时冻结时间
//    {0x05011001,    Data_RO,    49,     0,  2,  0x0B,   SSDJID,     1, },//（上1次）瞬时冻结变量数据
//    {0x05020001,    Data_RO,    49,     2,  1,  0x0B,   SQQHDJID,   2, },//（上1次）两套时区表切换时间
//    {0x05021001,    Data_RO,    49,     0,  1,  0x0B,   SQQHDJID,   2, },//（上1次）两套时区表切换变量数据
//    {0x05030001,    Data_RO,    49,     2,  1,  0x0B,   RSDQHDJID,  3, },//（上1次）两套日时段表切换时间
//    {0x05031001,    Data_RO,    49,     0,  1,  0x0B,   RSDQHDJID,  3, },//（上1次）两套日时段表切换变量数据
//    {0x05040001,    Data_RO,    13,     2,  253,0x0B,   ZDDJID,     4, },//（上1次）整点冻结时间
//    {0x05060001,    Data_RO,    49,     2,  61, 0x0B,   RDJID,      5, },//（上1次）日冻结时间
//    {0x05061001,    Data_RO,    49,     0,  61, 0x0B,   RDJID,      5, },//（上1次）日冻结变量数据
//}; 
/*******************************************************************************
**核心表6，主要是有关负荷记录的一些数据
*******************************************************************************/
//const   S_CORETAB code gs_CoreTab6[] = 
//{
//    //  ID            Atb      LEN     D1  D0  FUNID   ADDR
//    {0x06000000,    Data_RO,    0,      0,  2,  0x11,   0,     0, },// 总负荷记录
//    {0x06010000,    Data_RO,    0,      0,  2,  0x11,   0,     1, },// 第1类负荷记录
//    {0x06020000,    Data_RO,    0,      0,  2,  0x11,   0,     2, },// 第2类负荷记录
//    {0x06030000,    Data_RO,    0,      0,  2,  0x11,   0,     3, },// 第3类负荷记录
//    {0x06040000,    Data_RO,    0,      0,  2,  0x11,   0,     4, },// 第4类负荷记录
////    {0x06050000,    Data_RO,    0,      0,  2,  0x11,   0,     5, },// 第5类负荷记录
////    {0x06060000,    Data_RO,    0,      0,  2,  0x11,   0,     6, },// 第6类负荷记录
//
//};
/*******************************************************************************
**核心表A，主要是表计的一些参数
*******************************************************************************/
const   S_CORETAB code gs_CoreTab4F[] = 
{

    //  ID          Atb         LEN D1  D0  FUNID   ADDR
//    {0x4F000001,    0,  27, 0,  0,  0x08,   EEP_AUTOCAL,    0,},//自动校表指令
    {0x4F000A00,    0,  8,  0,  0,  0x12,   0,              0,},//读取版本号
    {0x4F010000,    0,  68, 0,  0,  0x0E,   0,              0,},//直接E2读写
    //{0x4F100000,    0,  0,  0,  0,  0x0F,   0,              0,},//打开生产模式
    //{0x4F110000,    0,  0,  0,  0,  0x0F,   0,              0,},//关闭生产模式,
};
 
/*=========================================================================================\n
* @function_name: gs_CoreID
* @function_file: ComCoretab.c
* @描述: 定义核心表与数据ID3的关系
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-10)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
const   S_COREID code gs_CoreID[] =       //核心数据表与ID的对应关系
{
//    {0x00,  (S_CORETAB code*)gs_CoreTab0, sizeof(gs_CoreTab0) / sizeof(S_CORETAB)},
    {0x02,  (S_CORETAB code*)gs_CoreTab2, sizeof(gs_CoreTab2) / sizeof(S_CORETAB)},
//    {0x03,  (S_CORETAB code*)gs_CoreTab3, sizeof(gs_CoreTab3) / sizeof(S_CORETAB)},
//    {0x04,  (S_CORETAB code*)gs_CoreTab4, sizeof(gs_CoreTab4) / sizeof(S_CORETAB)},
//    {0x05,  (S_CORETAB code*)gs_CoreTab5, sizeof(gs_CoreTab5) / sizeof(S_CORETAB)},
//    {0x06,  (S_CORETAB code*)gs_CoreTab6, sizeof(gs_CoreTab6) / sizeof(S_CORETAB)},
//    {0x07,  (S_CORETAB code*)gs_CoreTab7, sizeof(gs_CoreTab7) / sizeof(S_CORETAB)},
//    {0x1D,  (S_CORETAB code*)gs_CoreTab1D, sizeof(gs_CoreTab1D) / sizeof(S_CORETAB)},
//    {0x1E,  (S_CORETAB code*)gs_CoreTab1E, sizeof(gs_CoreTab1E) / sizeof(S_CORETAB)},
    {0x4F,  (S_CORETAB code*)gs_CoreTab4F, sizeof(gs_CoreTab4F) / sizeof(S_CORETAB)},
};

const   uint8 code NumofCoreID = sizeof(gs_CoreID) / sizeof(S_COREID);
