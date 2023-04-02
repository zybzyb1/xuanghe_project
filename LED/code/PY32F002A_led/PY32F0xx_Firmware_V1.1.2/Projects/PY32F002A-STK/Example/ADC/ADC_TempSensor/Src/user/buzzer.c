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
	  //to_PWM_value(0x7f);  //��������������Ƶ��2000
	  buzzer_time_set(2);  //250ms 
}

void buzzer_run(void)
{
    if(buzzerEnableFlag)//��������������Ƶ��2000
		{
			  if(buzzer_timer > buzzer_config_time)  //��ʱ��λ125ms
				{
						buzzerEnableFlag = 0;
						buzzer_timer =0;
					  buzzer_driver(0);//��1
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
		     buzzer_driver(1);  //1����ת 0����1 
		}
	

}
void buzzer_time_set(u8 time)//���÷������ʱ������ʱ��λ125ms
{
    buzzer_config_time = time;
}

