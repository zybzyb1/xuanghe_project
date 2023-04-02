#include  "led2_digital_tube.h"
#include  "global.h"
#include  "user_gpio.h"
#include  "timing.h"
#include  "py32f0xx_hal.h"
#include  "infrared.h"

u8  preDisplayV[2];
u8  digital_value[2];
u8  led_display_chang;
u8  timDisplay_value[2];//ͨ��2��ʾ���ݻ�����
u16 display_second=0;   //ͨ��2��ʾ���ʱ��
u8  shine_count;        //ͨ��2��ʾ��˸��ʱ��
u8  shine_enable;       //ͨ��2��ʾ��˸ʹ��
u8  area_shine_enable;  //��ʾ��˸ʹ��--�ֲ�  
/*************    ����˵��        *************

����8������������Զ�ɨ����ʾ.

******************************************/
static void led_display_unit(uint8 displayV,uint8 page);
void rdelay_acton_fun(u8 action_value);

void  led_display_init(void)
{
		led_display_chang=0;
	  shine_enable = 0;
}


void  led_display(void)  //10msִ��һ��
{
	  static u8 page=1;
    u8 dat1,dat2;

		if(led_display_chang==1 )     //��ʾͨ��2
		{
			   ++display_second;
			  if(shine_enable)
				{
						if(display_second <= 300)  //������λ10ms ǰ3s��˸��ʾ
							 area_shine_enable = 1;
						
						else if(display_second > 400)  //��2s����˸��ʾ
						{
								 display_second = 0;
								 shine_count = 0;
								 shine_enable =0;
								 area_shine_enable=0;
								 tming_parameter_save();  //���涨ʱ����
								 led_display_chang = 0;   //�л���0ͨ����ʾ
						}
						else 
							  area_shine_enable = 0;
				}
				else
				{
				    if(display_second > 300)  //������λ10ms ǰ3s��ʾ
				        led_display_chang = 0;   //�л���0ͨ����ʾ���ñ��慢��
				}
		}
		if(led_display_chang==2 && shine_enable)     //��ʾͨ��3 ��ʱʱ���޸Ľ�������ʾ
		{
		    area_shine_enable=1;
		}		
    if(led_display_chang==0)
		{
			 area_shine_enable=0;
			
		}
		
    if(area_shine_enable)
		{
		    //��˸��ʾ
				++shine_count;   //������λ10ms
				if(shine_count < 20)  //ǰ200ms����ʾ
				{
							DIG1_OFF;
							DIG2_OFF;
							return;
				}		
				else if(shine_count > 40)	//��200ms��ʾ�����γ���˸
							shine_count = 0;
		
		}
		
		
		if(led_display_chang==0)  //��ʾͨ��1 ��λ��ʾ
		{ 
			  dat1 = digital_value[0];
			  dat2 = digital_value[1];
			  display_second = 0;
			  shine_count = 0;
			  timing_enableFlag=0;
		}
		else                      //��ʾͨ2��3 ��ʱʱ����ʾ
		{
				dat1 = timDisplay_value[0];
				dat2 = timDisplay_value[1];
		}
		
		if(page == 1)
		{
				led_display_unit(dat1,page);
				page = 2;	  
		}
		else if(page == 2)
		{
				led_display_unit(dat2,page);
				page = 1;	  
		}
}	

static void led_display_unit(u8 displayV,u8 page)
{
     
		 DIG1_OFF;
		 DIG2_OFF;
	  
		 switch(displayV)
		 {
			 case 0:
			 DIGITAL_VALUE_PORT = 0x0000003f; //0x3F			 
			 break;
			 case 1:
			 DIGITAL_VALUE_PORT = 0x00000006; //0x06

			 break;
			 case 2:
			 DIGITAL_VALUE_PORT = 0x0000005b;  //0x5B 
			 break;
			 case 3:
			 DIGITAL_VALUE_PORT = 0x0000004f; //0x4F
			 break;
			 case 4:
			 DIGITAL_VALUE_PORT = 0x00000066; //0x66	 
			 break;
			 case 5:
			 DIGITAL_VALUE_PORT = 0x0000006d; //0x6D
			 break;
			 case 6:
			 DIGITAL_VALUE_PORT = 0x0000007d; //0x7D
			   
			 break;
			 case 7:
			 DIGITAL_VALUE_PORT = 0x00000007; //0x07
			 	 
			 break;
			 case 8:
			 DIGITAL_VALUE_PORT = 0x0000007f; //0x7F
			    
			 break;
			 case 9:
			 DIGITAL_VALUE_PORT = 0x0000006f; //0x6F
			  
			 break;
			 case 0x0A:
			 DIGITAL_VALUE_PORT = 0x00000077; //0x77
			  
			 break;
			 case 0x0B:
			 DIGITAL_VALUE_PORT = 0x0000007c; //0x7C
			 
			 break;
			 case 0x0C:
			 DIGITAL_VALUE_PORT = 0x00000039; //0x39
			 
			 break;
			 case 0x0D:
			 DIGITAL_VALUE_PORT = 0x0000006e; //0x5E
			 
			 break;
			 case 0x0E:
			 DIGITAL_VALUE_PORT = 0x00000079; //0x79
			  
			 break;
			 case 0x0F:
			 DIGITAL_VALUE_PORT = 0x00000071; //0x71
			   
			 break;
			 case 0x10: //'L'
			 DIGITAL_VALUE_PORT = 0x00000038; //0x38
			 break; 
			 default:  //'-'
			 DIGITAL_VALUE_PORT = 0x00000040; //0x40
			 
			 break;
		 }
 
		 if(page==1){DIG1_ON;}
		 else       {DIG2_ON;}
}


