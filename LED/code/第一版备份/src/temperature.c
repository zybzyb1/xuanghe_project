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
	
	  if(secFlag==1)  //1秒 ADC一次
		{
				secFlag = 0;
				ad_dat = Get_ADCResult(ADC_CH13);  //读取ADC定时值
			
				if(ad_dat == 4096)  return;   //出错
				
				if(ad_dat > 1024 / TIMER_LENGTH_MAX / 2)//定时功能开启
				{			
						if(ad_pre > ad_dat+15 || ad_pre < ad_dat-15)
						{
								ad_pre = ad_dat;
								timeFunFlag = 1;  //定时功能开启
								time_cnt = 0;   //定时计数器清零
								delay_time = calculate_timer(ad_dat); //计算出定时时长
						}
				}
				else
						timeFunFlag = 0;   //定时功能关闭
				
				if(timeFunFlag)
				{	
						if(time_unit_compare(delay_time))  
						{                     //定时时间到了
								btn_value=0;
								rdelay_acton_fun(0);
								timeFunFlag = 0;  //定时功能关闭
								sysFunFlag = 0;
						}	
				}			  
		}	  
}
static u8  time_unit_compare(u8 delayTime)
{
		u32 delay_T;
	
	  delay_T = delayTime*30*60;   //delayTime单位为半个小时 这里转化为秒
	   
	  if(time_cnt > delay_T)
		{
				time_cnt = 0; //定时计数清零
		    return 1;
		}
		return 0;
}
static u8  calculate_timer(u16 adValue)
{ 
	u8  timing_time=0;  //定时时长 单位1表小0.5小时
	u16 step_length = 1024 / TIMER_LENGTH_MAX; //这里计算定时步长对应的数值,当ADC值是低半步关闭定时功能,最高半步值时定时时长8个小时
  u16  half_length =  step_length/2;
	if(adValue < half_length)   //ADC数值小于32关闭定时
       timing_time = 0;
	else if(adValue > 1024- half_length) //ADC数值大于1024-32=992定时8小时
       timing_time = 16; //8 小时
	else
		{    // 计算定时时长步长为0.5小时  每一步长对应ADC数值64
			timing_time = adValue/step_length; 
			//ADC数值<=32 故timing_time=0 定时长为0小时，
			//32<ADC数值<=96 故timing_time=1 定时长为半小时，96<ADC数值<160 故timing_time=2 定时长为1小时 .160<ADC数值<224 故timing_time=3 定时长为1.5小时 
			//224<ADC数值<=288 故timing_time=4 定时长为2小时,288<ADC数值<352 故timing_time=5 定时长为2.5小时,352<ADC数值<416 故timing_time=6 定时长为3小时 
			//416<ADC数值<=480 故timing_time=7 定时长为3.5小时480<ADC数值<544 故timing_time=8 定时长为4小时 544<ADC数值<608 故timing_time=9 定时长为4.5小时 
			//608<ADC数值<=672 故timing_time=10 定时长为5小时,672<ADC数值<736 故timing_time=11 定时长为5.5小时,736<ADC数值<800 故timing_time=12 定时长为6小时
      //800<ADC数值<=864 故timing_time=13 定时长为6.5小时，864<ADC数值<928 故timing_time=14 定时长为7小时928<ADC数值<992 故timing_time=15 定时长为7.5小时 
			//992<ADC数值<=1024 故timing_time=16 定时长为8小时.			
	    if(adValue % step_length  > half_length)
				   timing_time++;
	
	}
		return timing_time;
}
//========================================================================
static void	ADC_config(void)
{
	
	ADC_InitTypeDef		ADC_InitStructure;		//结构定义
	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC 通道选择时间控制 0(默认),1
	ADC_InitStructure.ADC_CsHold    = 1;		//ADC 通道选择保持时间控制 0,1(默认),2,3
	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//初始化
	ADC_PowerControl(ENABLE);						//ADC电源开关, ENABLE或DISABLE
	//NVIC_ADC_Init(DISABLE,Polity_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Polity_0,Polity_1,Polity_2,Polity_3
	
}
#endif	
