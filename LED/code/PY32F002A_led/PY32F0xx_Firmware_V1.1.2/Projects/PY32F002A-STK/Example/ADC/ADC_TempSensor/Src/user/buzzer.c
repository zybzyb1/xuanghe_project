#include "buzzer.h"
#include "global.h"
#include "user_gpio.h"

u8 buzzerEnableFlag;
u8 buzzer_timer;
u8 buzzer_config_time;


void buzzer_time_set(u8 time);

void buzzer_init(void)
{
    buzzerEnableFlag =0;
	  //to_PWM_value(0x7f);  //蜂鸣器驱动脉冲频率2000
	  buzzer_time_set(2);  //250ms 
}

void buzzer_run(void)
{
    if(buzzerEnableFlag)//蜂鸣器驱动脉冲频率2000
		{
			  if(buzzer_timer > buzzer_config_time)  //计时单位125ms
				{
						buzzerEnableFlag = 0;
						buzzer_timer =0;
					  buzzer_driver(0);//置1
				}
		}
    else
		{
				 buzzer_timer = 0;		
			   
		}

}
void  buzzer_io_driver(void)
{
	  static u8 state=0;
    if(buzzerEnableFlag)
		{
		     buzzer_driver(1);  //1、翻转 0、置1 
		}
	

}
void buzzer_time_set(u8 time)//配置蜂器响的时长，计时单位125ms
{
    buzzer_config_time = time;
}

