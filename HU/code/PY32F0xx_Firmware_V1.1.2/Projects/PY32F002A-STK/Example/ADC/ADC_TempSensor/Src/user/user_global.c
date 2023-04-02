#include  "global.h"
#include  "infrared.h"
#include  "buzzer.h"
#include  "user_gpio.h"
#include  "led2_digital_tube.h"
#include  "encryptionDecryption.h"

/**************** 外部函数声明*****************/
void rdelay_acton_fun(u8 action_value);
void display_para(u8 bak);

//函数功能：备份与还原参数
void display_para(u8 bak)
{
   static u8 btn_value_bak=0xff;
	 if(1 == bak)
	    btn_value_bak = btn_value;
	 else
	 {
	     btn_value = btn_value_bak;
	     rdelay_acton_fun(btn_value);
	 }

}
void rdelay_acton_fun(u8 action_value)
{
	#if 1
	  buzzerEnableFlag = 1;
	  led_display_enable=1; 
	  if(method_res_compare())
		  action_value = 6;
		
    switch(action_value)
		{
		    case 0:  // 断开所有继电器
					led_display_enable=0;  //上电LED数码管不显示
				  si_level = 0; 
        break;
				case 1:   //数码管显示--
				    digital_value[0]=0xff;
				    digital_value[1]=0xff;	    
				    si_level = 0;
        break;
				case 2:  //数码管显示L1 
				    digital_value[0]=0x10;
				    digital_value[1]=0x01;
				    si_level = 1;
        break;
				case 3: 
				    digital_value[0]=0x10;
				    digital_value[1]=0x02;
				    si_level = 2;
        break;
				case 4: 
				    digital_value[0]=0x10;
				    digital_value[1]=0x03;
				    si_level = 3;
        break;
				case 5:  //数码管显示E1
				    digital_value[0]=0x0e;
				    digital_value[1]=0x01;
				    si_level = 0;
        break;
				case 6:  //数码管显示1E
				    digital_value[0]=0x01;
				    digital_value[1]=0x0e;
				    si_level = 0;
        break;
		    default:
					
				break;
		}
#endif
}

