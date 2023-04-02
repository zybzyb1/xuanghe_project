#include  "global.h"
#include  "infrared.h"
#include  "buzzer.h"
#include  "user_gpio.h"
#include  "led2_digital_tube.h"
#include  "encryptionDecryption.h"
#include  "timing.h"


/**************** �ⲿ��������*****************/
void rdelay_acton_fun(u8 action_value);
void display_para(u8 bak);
void timing_action_fun(u8 timing);

static u8 btn_value_bak=0xff;
static u8 led_display_chang_bak=0;
static u8 si_level_bak=0;

//�������ܣ������뻹ԭ����
void display_para(u8 bak)
{

	 if(1 == bak)   //����
	 {
	    btn_value_bak = btn_value;
		  led_display_chang_bak = led_display_chang; 
		  si_level_bak = si_level;
	 }
	 else
	 {         //��ԭ
	     btn_value = btn_value_bak;
	     rdelay_acton_fun(btn_value);
		   led_display_chang = led_display_chang_bak;
		   si_level = si_level_bak;
		   timing_action_fun(timing_duration);
	 }
   
}
void rdelay_acton_fun(u8 action_value)
{
	  buzzerEnableFlag = 1;
	  if(method_res_compare())
		   action_value = 6;
		
    switch(action_value)
		{
		    case 0:  // �Ͽ��ɿع裬�������ʾ00
				    digital_value[0]=0x00;
				    digital_value[1]=0x00;	    
				    si_level = 0;
        break;
				case 1:  //�������ʾL1 
				    digital_value[0]=0x10;
				    digital_value[1]=0x01;
				    si_level = 1;
        break;
				case 2: 
				    digital_value[0]=0x10;
				    digital_value[1]=0x02;
				    si_level = 2;
        break;
				case 3: 
				    digital_value[0]=0x10;
				    digital_value[1]=0x03;
				    si_level = 3;
        break;
				case 5:  //�������ʾE1
				    digital_value[0]=0x0e;
				    digital_value[1]=0x01;
				    si_level = 0;
        break;
				case 6:  //�������ʾ1E
				    digital_value[0]=0x01;
				    digital_value[1]=0x0e;
				    si_level = 0;
        break;
		    default:
					
				break;
		}

}
void timing_action_fun(u8 timing)
{
    buzzerEnableFlag = 1;
	 
    switch(timing)
		{
		    case 0:  // �Ͽ��ɿع裬�������ʾ00
				    timDisplay_value[0]=0xff;
				    timDisplay_value[1]=0xff;	    
        break;
				case 1:  //�������ʾ0X 
				case 2:
				case 3:
        case 4:					
				case 5:  //�������ʾ
				case 6:  //�������ʾ
				case 7:	
				case 8:
				    timDisplay_value[0]=0x00;
				    timDisplay_value[1]=timing;
        break;
		    default:
					
				break;
		}

}
void alarm_action_fun(u8 alarmType)
{
	  if(alarmType == OVERTEMPERTURE_TYPE)
		{
				timDisplay_value[0]=0x0e;
				timDisplay_value[1]=0x01;
		}
		else if(alarmType == UID_TYPE)
		{
				timDisplay_value[0] = 0x01;
				timDisplay_value[1] = 0x0e;
		}
			
}