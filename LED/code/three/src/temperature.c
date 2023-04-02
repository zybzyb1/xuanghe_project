#include "temperature.h"
#include "adc.h"
#include  "stc8g1k_code.h"
#include "uart.h"
bit overtemperature_flag;   //���±�����־
bit overtemp_flag;          //���±�����ʱ��־
bit secFlag;       //���־
u8  delay_time;

static void	ADC_config(void);

void temperature_init(void)
{
    overtemperature_flag = 0;
	  overtemp_flag = 0;
		secFlag=0;			
		delay_time=0;
	  ADC_config();   //��·���¶ȼ��	
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
				ad_dat = Get_ADCResult(ADC_CH5);  //��ȡADC��ʱֵ
			  #ifdef UART_ENABLE
			  TX1_write2buff((u8)(ad_dat>>8));
			  TX1_write2buff((u8)ad_dat);
			  #endif	
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
	static bit  preOvertemperature_flag = 0;
	
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
//========================================================================
static void	ADC_config(void)
{
	
	ADC_InitTypeDef		ADC_InitStructure;		//�ṹ����
	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
	ADC_InitStructure.ADC_CsHold    = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//��ʼ��
	ADC_PowerControl(ENABLE);						//ADC��Դ����, ENABLE��DISABLE
	//NVIC_ADC_Init(DISABLE,Polity_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
	
}

