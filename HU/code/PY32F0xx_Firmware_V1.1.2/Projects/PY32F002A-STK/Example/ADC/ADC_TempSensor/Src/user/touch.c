/*******************��������*******************
��������

1����һ�δ����̵���1 (PCB�����������̵���)��ͨ220V��Դ��

2���ڶ��δ����̵���1 (PCB�����������̵���)�Ͽ����̵���2 (PCB���м�̵���)��ͨ220V��Դ��

3�������δ����̵���1 �����̵���2 ����ͨ220V��Դ��

4�����Ĵδ����ֻص���һ�δ���ʵ�ֵĹ��ܣ�ֻ��(PCB�����������̵���)��ͨ220V��Դ��
************************************************/

#include  "touch.h"
#include  "infrared.h"
#include  "global.h"
#include  "user_gpio.h"
#include  "py32f0xx_hal.h"

//#define   TOUCH_PIN      read_touch()

u16 Touch_time;      //������ʱ��
u8 Touch_flag=0;    //����IC�����־
u8 touch_preFlag=0; //�ϴδ���IC�����־

static  u8 touch_check(void);    //�������
static void touch_deal(void);    //��������
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
/*************��������*********************/
static  u8 touch_check(void)
{   //����������   �޴���ʱ�ߵ�ƽ���д���ʱ�͵�ƽʱ������200ms
    if(read_touch() == 0)
    {
			   if(Touch_flag)					 
					 Touch_time = 0;
         else if(Touch_time > 300)  //250΢�� *300 = 75ms
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
						if(Touch_time > 800)  //250΢�� *800 = 200ms
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

