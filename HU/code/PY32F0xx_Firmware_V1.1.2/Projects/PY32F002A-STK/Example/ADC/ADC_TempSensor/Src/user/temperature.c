#include "temperature.h"
#include  "stc8g1k_code.h"
#include  "global.h"

u8 overtemperature_flag;   //���±�����־
u8 overtemp_flag;          //���±�����ʱ��־
u8 secFlag;       //���־
u8  delay_time;
u16  aADCxConvertedData;


void temperature_init(void)//��·���¶ȼ��	
{
    overtemperature_flag = 0;
	  overtemp_flag = 0;
		secFlag=0;			
		delay_time=0;
	  //ADC_config();   
}
#define    TEMP70_VAL    477    //70�ȶ�Ӧ��ADCֵ  0X1DD
#define    TEMP60_VAL    556    //60�ȶ�Ӧ��ADCֵ  0X22C

//------------------------------------------------
void  temperature_get_deal(void)
{
	  u16  ad_dat;
	 
	  if(secFlag==1)  //1�� ADCһ��
		{
				secFlag = 0;
			  
				ad_dat = aADCxConvertedData; //Get_ADCResult(ADC_CH5);  //��ȡADC��ʱֵ
			 	
				if(ad_dat == 4096)  return;   //����
				
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
u8 overtemperature_check(void)
{
	static u8  preOvertemperature_flag = 0;
	
	if(overtemperature_flag ==1)
	{
		  rdelay_acton_fun(5);
		  if(preOvertemperature_flag ==0)
			{
			    display_para(1);
		      preOvertemperature_flag = 1; 
			}
			return 1;
	}
	else
	{
	    if(preOvertemperature_flag)
			{
			    preOvertemperature_flag =0;
				  display_para(0);
			}
	}
	return 0;
}

