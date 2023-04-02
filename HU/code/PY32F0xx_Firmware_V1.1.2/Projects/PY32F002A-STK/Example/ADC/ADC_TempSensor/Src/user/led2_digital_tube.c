#include  "led2_digital_tube.h"
#include  "global.h"
#include  "user_gpio.h"
#include  "py32f0xx_hal.h"

u8  preDisplayV[2];
u8  digital_value[2];
u8  led_display_enable;
/*************    功能说明        *************

驱动8个共阴数码管自动扫描显示.

******************************************/
static void led_display_unit(uint8 displayV,uint8 page);
void rdelay_acton_fun(u8 action_value);

void  led_display_init(void)
{
		led_display_enable=0;
}

void  led_display(void)
{
	  static u8 page=1;
    
	  if(led_display_enable)
		{
			if(page == 1)
			{
					led_display_unit(digital_value[0],page);
					page = 2;	  
			}
			else if(page == 2)
			{
					led_display_unit(digital_value[1],page);
					page = 1;	  
			}
		}
		else
		{
			 DIG1_OFF;
		   DIG2_OFF;
		}
}	

static void led_display_unit(u8 displayV,u8 page)
{
     
		 DIG1_OFF;
		 DIG2_OFF;
#if 1		
		 switch(displayV)
		 {
			 case 0:
			 digital_value_port = 0x0000003f; //0x3F
			 
			 break;
			 case 1:
			 digital_value_port = 0x00000006; //0x06
			   
			 break;
			 case 2:
			 digital_value_port = 0x0000005b;  //0x5B
			   
			 break;
			 case 3:
			 digital_value_port = 0x0000004f; //0x4F
			 	 
			 break;
			 case 4:
			 digital_value_port = 0x00000066; //0x66	 
			 break;
			 case 5:
			 digital_value_port = 0x0000006d; //0x6D
			 break;
			 case 6:
			 digital_value_port = 0x0000007d; //0x7D
			   
			 break;
			 case 7:
			 digital_value_port = 0x00000007; //0x07
			 	 
			 break;
			 case 8:
			 digital_value_port = 0x0000007f; //0x7F
			    
			 break;
			 case 9:
			 digital_value_port = 0x0000006f; //0x6F
			  
			 break;
			 case 0x0A:
			 digital_value_port = 0x00000077; //0x77
			  
			 break;
			 case 0x0B:
			 digital_value_port = 0x0000007c; //0x7C
			 
			 break;
			 case 0x0C:
			 digital_value_port = 0x00000039; //0x39
			 
			 break;
			 case 0x0D:
			 digital_value_port = 0x0000006e; //0x5E
			 
			 break;
			 case 0x0E:
			 digital_value_port = 0x00000079; //0x79
			  
			 break;
			 case 0x0F:
			 digital_value_port = 0x00000071; //0x71
			   
			 break;
			 case 0x10: //'L'
			 digital_value_port = 0x00000038; //0x38
			 
			 break; 
			 default:  //'-'
			 digital_value_port = 0x00000040; //0x40
			  
			 break;
		 }
#endif	 
		 if(page==1){DIG1_ON;}
		 else       {DIG2_ON;}
}


