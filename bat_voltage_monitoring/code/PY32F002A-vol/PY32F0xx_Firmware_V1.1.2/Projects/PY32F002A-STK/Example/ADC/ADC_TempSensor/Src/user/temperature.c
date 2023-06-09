#include  "temperature.h"
#include  "global.h"
#include  "user_gpio.h"
#include  "infrared.h"
#include  "led2_digital_tube.h"

#define    ADCBUFFER_SIZE  10
#define    POWER_VOL      18830//20000//18830     //电源电压mv 18.787v

u8   secFlag;       //秒标志
u8   ad_done_flag;  //ADC转换完成标志
u16  aADCxConvertedData;
u16  aADC[ADCBUFFER_SIZE];
u8   adcConverterCnt;
u16  vol_value;
u8   vol_enable;
u8 firstcnt;
 
static void cal_vol(u32 vol);

void temperature_init(void)//电路板温度检测	
{
		secFlag=1;			
	  ad_done_flag = 0;
	  adcConverterCnt =0;
	  vol_value = 1;
	  vol_enable = 1;
	  firstcnt = 0;
}
//分压计算公司 Rt/(Rt+2) = V/3.3
//TEMP70:1.745/(1.745+2) = V/3.3  V33 = 1.537V  V50 = 2.329V
//TEMP60:2.477/(2.477+2) = V/3.3  V33 = 1.825V  V50 = 2.766V 
#define    TEMP70_VAL    1907    //70度对应的ADC值 1907   电阻1.745k   Rt/(Rt+2) = V/3.3 
#define    TEMP60_VAL    2265    //60度对应的ADC值 2265   电阻2.477k 上拉电阻2K

//------------------------------------------------
void  val_get_deal(void)
{
	  u8  i;
	  u16  ad_dat,ad_min=0xffff,ad_max=0;
	  u32  adVar=0;
	
	  if(vol_enable==0)
		{
			 ad_done_flag =0;
			 adcConverterCnt =0; 
			 secFlag = 0;
			 return;
		}
	  if(secFlag==1)  //10m秒 ADC一次
		{
				secFlag = 0;
			  ad_done_flag=0;
			  adc_enable();
		}	
    else if(ad_done_flag==1)
		{			
			  ad_done_flag= 0;
			
				aADC[adcConverterCnt] = aADCxConvertedData;   //读取ADC定时值
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
            adVar = adVar - ad_min - ad_max;	//去最大与最小值
						
            ad_dat = (u16)(adVar>>3);	//取平均值
		
						cal_vol(ad_dat);  
            vol_enable = 0;						
				}
			  else if(firstcnt == 0)
				{
				    cal_vol(aADCxConvertedData);
					  firstcnt = 1;
				}
		}	
   	
}
//ADC 电压转换公式
// R5/(R4+R5)  * OUT_VOL =  vol / 4096  * 5000 
// 3.3/(3.3+9.1) * OUT_VOL =  vol / 4096  * 5000 
// OUT_VOL = vol / 4096  * 5000 / (3.3/(3.3+9.1))  0.2661290
static void cal_vol(u32 vol)
{
	  u16 ad_dat;
	  //u32 tmp;
	  
	  //tmp = vol * POWER_VOL;
	  //tmp = tmp / 4096;
   	ad_dat = (u16)(vol * POWER_VOL / 4096);//tmp; //
    
	  vol_value = ad_dat/100;
    vol_value += 6;
}
