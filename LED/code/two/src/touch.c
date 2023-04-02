#include  "touch.h"
#include  "infrared.h"
#include  "global.h"
#include  "STC8xxxx.h"	
#include  "stc8g1k_code.h"
#include  "uart.h"

#define   TOUCH_PIN      P36
sfr INTCLKO = 0x8f;

u16 Touch_time;      //������ʱ��
bit Touch_flag=0;    //����IC�����־
bit touch_preFlag=0; //�ϴδ���IC�����־

static  u8 touch_check(void);    //�������
static void touch_deal(void);    //��������

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
/*************��������*********************/
static  u8 touch_check(void)
{   //����������   �޴���ʱ�ߵ�ƽ���д���ʱ�͵�ƽʱ������300ms
    if(TOUCH_PIN == 1)
    {
			   if(Touch_flag)					 
					 Touch_time = 0;
         else if(Touch_time > 500)  //139΢�� *500 = 69.5ms
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
						if(Touch_time > 2000)  //139΢�� *2000 = 279.5ms
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
//-------------------------�ⲿ�ж�3����������ʼ��-------------------------
static void Int2_init(void)
{
	EX0 = 1;	//ʹ��INT0�ж�
	INTCLKO = EX2; //ʹ�� INT2 �½����ж�
  //INTCLKO |= EX3; //ʹ�� INT3 �½����ж�//������ʽΪ�½��ش���
  //INTCLKO |= EX4; //ʹ�� INT4 �½����ж�
}
