
#include "V98xx.h"
#include "TestFunc.h"
#include "delay.h"

#pragma location = "BANK2"

/*************************************************
功能：在此页下设置LED闪烁次数
函数名：call_bank2
入口参数：unsinged char i
出口参数：返回值为空
*************************************************/
__banked_func void call_bank2(unsigned char i)
{
	unsigned char count;
	count=i;
	while(count--)//如果在BANK2区间代码闪烁7次
	{  
		LED_ON();
		delay_100ms(2);
		LED_OFF();
		delay_100ms(2);		  
	}
}
