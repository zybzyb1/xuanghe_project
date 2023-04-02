#include  "touch.h"
#include  "infrared.h"
#include  "global.h"
#include  "STC8xxxx.h"	
#include  "stc8g1k_code.h"
#include  "uart.h"

#define   TOUCH_PIN      P36
sfr INTCLKO = 0x8f;

u16 Touch_time;      //触摸计时器
bit Touch_flag=0;    //触摸IC输出标志
bit touch_preFlag=0; //上次触摸IC输出标志

static  u8 touch_check(void);    //触摸检测
static void touch_deal(void);    //触摸处理

void  touch_init(void)
{
    Touch_time = 0;
	  Touch_flag = 0;  
	  touch_preFlag = 0;
}

void  touch_check_deal(void)
{
    touch_check();
    touch_deal();
}
/*************触摸功能*********************/
static  u8 touch_check(void)
{   //触摸输出检测   无触摸时高电平，有触摸时低电平时长大于300ms
    if(TOUCH_PIN == 1)
    {
			   if(Touch_flag)					 
					 Touch_time = 0;
         else if(Touch_time > 500)  //139微秒 *500 = 69.5ms
				 {
					    Touch_time = 0;
				      Touch_flag = 1;     
					    return 1;
				 }
         			 
    }
		else 
		{
				if(Touch_flag)
				{
						if(Touch_time > 2000)  //139微秒 *2000 = 279.5ms
						{
							 Touch_time=0;
							 Touch_flag = 0;
						}
				}
				else 
				{
					  Touch_time=0;
					
				} 
		}
		return 0;
}

static void touch_deal(void)
{
	 if(Touch_flag)
	 {
			if(!touch_preFlag)
			{
					touch_preFlag = 1;
				  btn_value++;
				  sysFunFlag = 1;
				
					if(btn_value > BUTTON_VALUE_MAX)
					{
							btn_value = 0;	
              sysFunFlag = 0;						
					}						
				  rdelay_acton_fun(btn_value);	
			}
	 }
	 else 
	 {
			touch_preFlag = 0;	
	 }
}
//-------------------------外部中断3触摸按键初始化-------------------------
static void Int2_init(void)
{
	EX0 = 1;	//使能INT0中断
	INTCLKO = EX2; //使能 INT2 下降沿中断
  //INTCLKO |= EX3; //使能 INT3 下降沿中断//触发方式为下降沿触发
  //INTCLKO |= EX4; //使能 INT4 下降沿中断
}
