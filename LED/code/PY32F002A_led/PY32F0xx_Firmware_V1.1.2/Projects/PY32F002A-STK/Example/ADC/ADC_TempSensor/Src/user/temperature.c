#include "temperature.h"
#include  "stc8g1k_code.h"
#include  "global.h"
#include  "user_gpio.h"
#include  "infrared.h"
#include  "led2_digital_tube.h"

#define    ADCBUFFER_SIZE  10

u8 overtemperature_flag;   //���±�����־
u8 overtemp_flag;          //���±�����ʱ��־
u8 secFlag;       //���־
u8 ad_done_flag;  //ADCת����ɱ�־
u8  delay_time;
u16  aADCxConvertedData;
u16  aADC[ADCBUFFER_SIZE];
u8  adcConverterCnt;

void temperature_init(void)//��·���¶ȼ��	
{
    overtemperature_flag = 0;
	  overtemp_flag = 0;
		secFlag=0;			
		delay_time=0;
	  ad_done_flag=0;  
	  adcConverterCnt =0;
}
//��ѹ���㹫˾ Rt/(Rt+2) = V/3.3
//TEMP70:1.745/(1.745+2) = V/3.3  V33 = 1.537V  V50 = 2.329V
//TEMP60:2.477/(2.477+2) = V/3.3  V33 = 1.825V  V50 = 2.766V 
#define    TEMP70_VAL    1907    //70�ȶ�Ӧ��ADCֵ 1907   ����1.745k   Rt/(Rt+2) = V/3.3 
#define    TEMP60_VAL    2265    //60�ȶ�Ӧ��ADCֵ 2265   ����2.477k ��������2K

//------------------------------------------------
void  temperature_get_deal(void)
{
	  u8  i;
	  u16  ad_dat,ad_min=0xffff,ad_max=0;
	  u32  adVar=0;
    
	  if(secFlag==1)  //1�� ADCһ��
		{
				secFlag = 0;
			  ad_done_flag=0;
			  adc_enable();
		}	
    else if(ad_done_flag==1)
		{			
			  ad_done_flag= 0;
			
				aADC[adcConverterCnt] = aADCxConvertedData;   //��ȡADC��ʱֵ
			 	++adcConverterCnt;

        if(adcConverterCnt >= ADCBUFFER_SIZE)	
				{	
            for(i=0;i<ADCBUFFER_SIZE ;i++)
            {
							  if(ad_min > aADC[i])
									 ad_min = aADC[i];
								if(ad_max < aADC[i])
									 ad_max = aADC[i];
								
						      adVar += aADC[i];	
						} 
            adVar = adVar - ad_min - ad_max;
						
            ad_dat = (u16)(adVar>>3);
						
						if(ad_dat < TEMP70_VAL)//����70�� �������ܿ���  �¶�Խ��ADCֵԽ��
						{			
								overtemp_flag = 1;  //�������ܿ���
												
						}
						else if(ad_dat > TEMP60_VAL)//����60�� �������ܹر�   �¶�Խ��ADCֵԽ��
						{
								overtemp_flag = 0;  //��ʱ���ܹر�	   				
						}	
						else 
						{
								 delay_time=0;
								 return;
						}
						if(delay_time++ > 4)   //������־״̬����5�����ϲſ�ȷ��
						{
								 overtemperature_flag = overtemp_flag;
								 delay_time =0; 
						}
				}
			 
		}	
   	
}
u8 overtemperature_check(void)
{
	static u8  preOvertemperature_flag = 0;
	
	if(overtemperature_flag ==1)
	{
		  if(si_level > 0)
			{
				 si_level = 1;
				
			}
		  alarm_action_fun(OVERTEMPERTURE_TYPE);
			led_display_chang=2;    //��ʾͨ��3
		  if(preOvertemperature_flag ==0)
			{
			    display_para(1);
		      preOvertemperature_flag = 1; 
				  shine_enable = 1;
			}
			return 1;
	}
	else
	{
	    if(preOvertemperature_flag)
			{
			    preOvertemperature_flag =0;
				  display_para(0);
				  shine_enable = 0;
			}
	}
	return 0;
}

