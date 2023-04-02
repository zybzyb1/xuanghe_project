#include  "led2_digital_tube.h"
#include  "global.h"
#include  "STC8G_H_GPIO.h"
#include  "uart.h"
u8  preDisplayV[2];
u8  digital_value[2];
u8  led_display_enable;
/*************    功能说明        *************

驱动8个共阴数码管自动扫描显示.

******************************************/
static void led_display_unit(uint8 displayV,uint8 page);

/**************** 外部函数声明*****************/


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
		
		 switch(displayV)
		 {
			 case 0:
			 A_OOUT(1); B_OOUT(1); C_OOUT(1); D_OOUT(1); //0x3F
			 E_OOUT(1); F_OOUT(1); G_OOUT(0);  
			 break;
			 case 1:
			 A_OOUT(0); B_OOUT(1); C_OOUT(1); D_OOUT(0);  //0x06
			 E_OOUT(0); F_OOUT(0); G_OOUT(0);  
			 break;
			 case 2:
			 A_OOUT(1); B_OOUT(1); C_OOUT(0); D_OOUT(1);  //0x5B
			 E_OOUT(1); F_OOUT(0); G_OOUT(1);	 
			 break;
			 case 3:
			 A_OOUT(1); B_OOUT(1); C_OOUT(1); D_OOUT(1); //0x4F
			 E_OOUT(0); F_OOUT(0); G_OOUT(1);	 	 
			 break;
			 case 4:
			 A_OOUT(0); B_OOUT(1); C_OOUT(1); D_OOUT(0); //0x66
			 E_OOUT(0); F_OOUT(1); G_OOUT(1);	 	 
			 break;
			 case 5:
			 A_OOUT(1); B_OOUT(0); C_OOUT(1); D_OOUT(1); //0x6D
			 E_OOUT(0); F_OOUT(1); G_OOUT(1);	 
			 break;
			 case 6:
			 A_OOUT(1); B_OOUT(1); C_OOUT(1); D_OOUT(1); //0x7D
			 E_OOUT(1); F_OOUT(1); G_OOUT(1);	 	 
			 break;
			 case 7:
			 A_OOUT(1); B_OOUT(1); C_OOUT(1); D_OOUT(0); //0x07
			 E_OOUT(0); F_OOUT(0); G_OOUT(0);	 	 
			 break;
			 case 8:
			 A_OOUT(1); B_OOUT(1); C_OOUT(1); D_OOUT(1); //0x7F
			 E_OOUT(1); F_OOUT(1); G_OOUT(1);	  
			 break;
			 case 9:
			 A_OOUT(1); B_OOUT(1); C_OOUT(1); D_OOUT(1); //0x6F
			 E_OOUT(0); F_OOUT(1); G_OOUT(1);		 
			 break;
			 case 0x0A:
			 A_OOUT(1); B_OOUT(1); C_OOUT(1); D_OOUT(0); //0x77
			 E_OOUT(1); F_OOUT(1); G_OOUT(1);	 
			 break;
			 case 0x0B:
			 A_OOUT(0); B_OOUT(0); C_OOUT(1); D_OOUT(1); //0x7C
			 E_OOUT(1); F_OOUT(1); G_OOUT(1);	  
			 break;
			 case 0x0C:
			 A_OOUT(1); B_OOUT(0); C_OOUT(1); D_OOUT(1); //0x39
			 E_OOUT(1); F_OOUT(1); G_OOUT(1);	  
			 break;
			 case 0x0D:
			 A_OOUT(0); B_OOUT(1); C_OOUT(1); D_OOUT(1); //0x5E
			 E_OOUT(1); F_OOUT(0); G_OOUT(1);	 
			 break;
			 case 0x0E:
			 A_OOUT(1); B_OOUT(0); C_OOUT(0); D_OOUT(1); //0x79
			 E_OOUT(1); F_OOUT(1); G_OOUT(1);	 
			 break;
			 case 0x0F:
			 A_OOUT(1); B_OOUT(1); C_OOUT(0); D_OOUT(1); //0x71
			 E_OOUT(1); F_OOUT(0); G_OOUT(0);	 
			 break;
			 case 0x10: //'L'
			 A_OOUT(0); B_OOUT(0); C_OOUT(0); D_OOUT(1); //0x38
			 E_OOUT(1); F_OOUT(1); G_OOUT(0);	 
			 break; 
			 default:  //'-'
			 A_OOUT(0); B_OOUT(0); C_OOUT(0); D_OOUT(0); //0x40
			 E_OOUT(0); F_OOUT(0); G_OOUT(1);	 
			 break;
		 }
	 
		 if(page==1){DIG1_ON;}
		 else       {DIG2_ON;}
}


