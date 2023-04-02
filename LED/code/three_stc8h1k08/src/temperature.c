#include "temperature.h"
#include "adc.h"
#include  "stc8g1k_code.h"
#include "uart.h"
bit overtemperature_flag;   //过温报警标志
bit overtemp_flag;          //过温报警临时标志
bit secFlag;       //秒标志
u8  delay_time;

static void	ADC_config(void);

void temperature_init(void)
{
    overtemperature_flag = 0;
	  overtemp_flag = 0;
		secFlag=0;			
		delay_time=0;
	  ADC_config();   //电路板温度检测	
}
#define    TEMP70_VAL    477    //70度对应的ADC值  0X1DD
#define    TEMP60_VAL    556    //60度对应的ADC值  0X22C

//------------------------------------------------
void  temperature_get_deal(void)
{
	  u16  ad_dat;
	 
	  if(secFlag==1)  //1秒 ADC一次
		{
				secFlag = 0;
				ad_dat = Get_ADCResult(ADC_CH5);  //读取ADC定时值
			  #ifdef UART_ENABLE
			  TX1_write2buff((u8)(ad_dat>>8));
			  TX1_write2buff((u8)ad_dat);
			  #endif	
				if(ad_dat == 4096)  return;   //出错
				
				if(ad_dat < TEMP70_VAL)//高于70度 保护功能开启  温度越高ADC值越低
				{			
						overtemp_flag = 1;  //保护功能开启
            				
				}
				else if(ad_dat > TEMP60_VAL)//低于60度 保护功能关闭   温度越高ADC值越低
				{
						overtemp_flag = 0;  //定时功能关闭	   				
				}	
        else 
				{
					   delay_time=0;
					   return;
				}
        if(delay_time++ > 4)   //报警标志状态保持5秒以上才可确定
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

