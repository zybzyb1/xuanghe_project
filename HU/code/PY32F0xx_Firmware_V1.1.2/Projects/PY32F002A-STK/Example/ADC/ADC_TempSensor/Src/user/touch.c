/*******************功能描述*******************
触摸功能

1、第一次触摸继电器1 (PCB板最边上这个继电器)接通220V电源。

2、第二次触摸继电器1 (PCB板最边上这个继电器)断开，继电器2 (PCB板中间继电器)接通220V电源。

3、第三次触摸继电器1 、摸继电器2 都接通220V电源。

4、第四次触摸又回到第一次触摸实现的功能，只有(PCB板最边上这个继电器)接通220V电源。
************************************************/

#include  "touch.h"
#include  "infrared.h"
#include  "global.h"
#include  "user_gpio.h"
#include  "py32f0xx_hal.h"

//#define   TOUCH_PIN      read_touch()

u16 Touch_time;      //触摸计时器
u8 Touch_flag=0;    //触摸IC输出标志
u8 touch_preFlag=0; //上次触摸IC输出标志

static  u8 touch_check(void);    //触摸检测
static void touch_deal(void);    //触摸处理
extern void rdelay_acton_fun(u8 action_value);

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
{   //触摸输出检测   无触摸时高电平，有触摸时低电平时长大于200ms
    if(read_touch() == 0)
    {
			   if(Touch_flag)					 
					 Touch_time = 0;
         else if(Touch_time > 300)  //250微秒 *300 = 75ms
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
						if(Touch_time > 800)  //250微秒 *800 = 200ms
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
				  RED_OFF();
				  GREEN_ON();
				
					if(btn_value >= BUTTON_VALUE_MAX)
					{
							btn_value = 0;	
              sysFunFlag = 0;	
              RED_ON();
				      GREEN_OFF();						
					}					
				  rdelay_acton_fun(btn_value);	
			}
	 }
	 else 
	 {
			touch_preFlag = 0;	
	 }
}

