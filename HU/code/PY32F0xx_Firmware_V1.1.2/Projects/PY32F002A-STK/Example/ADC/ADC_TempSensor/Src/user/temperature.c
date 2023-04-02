#include "temperature.h"
#include  "stc8g1k_code.h"
#include  "global.h"

u8 overtemperature_flag;   //过温报警标志
u8 overtemp_flag;          //过温报警临时标志
u8 secFlag;       //秒标志
u8  delay_time;
u16  aADCxConvertedData;


void temperature_init(void)//电路板温度检测	
{
    overtemperature_flag = 0;
	  overtemp_flag = 0;
		secFlag=0;			
		delay_time=0;
	  //ADC_config();   
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
			  
				ad_dat = aADCxConvertedData; //Get_ADCResult(ADC_CH5);  //读取ADC定时值
			 	
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

