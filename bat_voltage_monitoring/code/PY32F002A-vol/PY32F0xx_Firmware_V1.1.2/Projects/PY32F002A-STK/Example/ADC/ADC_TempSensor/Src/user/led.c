#include  "led.h"
#include  "user_gpio.h"
#include  "global.h"

u8 led_mode;

void led_init(void)
{
     led_mode = 0;


}
void led_run(void)
{

   switch(led_mode)
	{
		case 0:
		{
			 LED_RED_OFF();
			 LED_GREEN_OFF();
			 break;
		}
		case 1:
		{
			LED_RED_ON();
			LED_GREEN_OFF();
			break;
		}
		case 2:
		{
			LED_RED_OFF();
			LED_GREEN_ON();
			break;
		}
		case 3:
		{
			LED_RED_ON();
			LED_GREEN_ON();
			break;
		}
	  default:
		
		break;
	
	}
  
}





