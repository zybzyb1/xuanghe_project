#include "temperature.h"

bit overtemperature_flag;


#ifdef  ADC_ENABLE	
void temperature_init(void)
{
    overtemperature_flag = 0;
					
		
}
//------------------------------------------------
void  temperature_get_deal(void)
{
	  u16  ad_dat;
	  static u16  ad_pre=0xffff;
	  static u8  delay_time=0;
	
	  if(secFlag==1)  //1�� ADCһ��
		{
				secFlag = 0;
				ad_dat = Get_ADCResult(ADC_CH13);  //��ȡADC��ʱֵ
			
				if(ad_dat == 4096)  return;   //����
				
				if(ad_dat > 1024 / TIMER_LENGTH_MAX / 2)//��ʱ���ܿ���
				{			
						if(ad_pre > ad_dat+15 || ad_pre < ad_dat-15)
						{
								ad_pre = ad_dat;
								timeFunFlag = 1;  //��ʱ���ܿ���
								time_cnt = 0;   //��ʱ����������
								delay_time = calculate_timer(ad_dat); //�������ʱʱ��
						}
				}
				else
						timeFunFlag = 0;   //��ʱ���ܹر�
				
				if(timeFunFlag)
				{	
						if(time_unit_compare(delay_time))  
						{                     //��ʱʱ�䵽��
								btn_value=0;
								rdelay_acton_fun(0);
								timeFunFlag = 0;  //��ʱ���ܹر�
								sysFunFlag = 0;
						}	
				}			  
		}	  
}
static u8  time_unit_compare(u8 delayTime)
{
		u32 delay_T;
	
	  delay_T = delayTime*30*60;   //delayTime��λΪ���Сʱ ����ת��Ϊ��
	   
	  if(time_cnt > delay_T)
		{
				time_cnt = 0; //��ʱ��������
		    return 1;
		}
		return 0;
}
static u8  calculate_timer(u16 adValue)
{ 
	u8  timing_time=0;  //��ʱʱ�� ��λ1��С0.5Сʱ
	u16 step_length = 1024 / TIMER_LENGTH_MAX; //������㶨ʱ������Ӧ����ֵ,��ADCֵ�ǵͰ벽�رն�ʱ����,��߰벽ֵʱ��ʱʱ��8��Сʱ
  u16  half_length =  step_length/2;
	if(adValue < half_length)   //ADC��ֵС��32�رն�ʱ
       timing_time = 0;
	else if(adValue > 1024- half_length) //ADC��ֵ����1024-32=992��ʱ8Сʱ
       timing_time = 16; //8 Сʱ
	else
		{    // ���㶨ʱʱ������Ϊ0.5Сʱ  ÿһ������ӦADC��ֵ64
			timing_time = adValue/step_length; 
			//ADC��ֵ<=32 ��timing_time=0 ��ʱ��Ϊ0Сʱ��
			//32<ADC��ֵ<=96 ��timing_time=1 ��ʱ��Ϊ��Сʱ��96<ADC��ֵ<160 ��timing_time=2 ��ʱ��Ϊ1Сʱ .160<ADC��ֵ<224 ��timing_time=3 ��ʱ��Ϊ1.5Сʱ 
			//224<ADC��ֵ<=288 ��timing_time=4 ��ʱ��Ϊ2Сʱ,288<ADC��ֵ<352 ��timing_time=5 ��ʱ��Ϊ2.5Сʱ,352<ADC��ֵ<416 ��timing_time=6 ��ʱ��Ϊ3Сʱ 
			//416<ADC��ֵ<=480 ��timing_time=7 ��ʱ��Ϊ3.5Сʱ480<ADC��ֵ<544 ��timing_time=8 ��ʱ��Ϊ4Сʱ 544<ADC��ֵ<608 ��timing_time=9 ��ʱ��Ϊ4.5Сʱ 
			//608<ADC��ֵ<=672 ��timing_time=10 ��ʱ��Ϊ5Сʱ,672<ADC��ֵ<736 ��timing_time=11 ��ʱ��Ϊ5.5Сʱ,736<ADC��ֵ<800 ��timing_time=12 ��ʱ��Ϊ6Сʱ
      //800<ADC��ֵ<=864 ��timing_time=13 ��ʱ��Ϊ6.5Сʱ��864<ADC��ֵ<928 ��timing_time=14 ��ʱ��Ϊ7Сʱ928<ADC��ֵ<992 ��timing_time=15 ��ʱ��Ϊ7.5Сʱ 
			//992<ADC��ֵ<=1024 ��timing_time=16 ��ʱ��Ϊ8Сʱ.			
	    if(adValue % step_length  > half_length)
				   timing_time++;
	
	}
		return timing_time;
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
#endif	
