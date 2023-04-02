#include  "timing.h"
#include  "global.h"
#include "user_flash.h"
#include "py32f002xx_Start_Kit.h"
#include  "infrared.h"

u8   timing_enable;     //定时使能标志
u8   timing_duration;   //定时时长
u32  cur_timer;         //定时计数器 以秒为单位


static u8 readTimingParam(void);
static void saveTimingParam(u8 timer);

void timing_init(void)
{
    cur_timer = 0;
	#if 0 
    timing_duration = readTimingParam();   //从FLASH读取定时参数
	  if(timing_duration >0 && timing_duration <= TIMING_VALUE_MAX)  //定时值在1-8小时内有效
			   timing_enable = 1;    //定时功能开启	
		else  
	#endif
		{  
			   timing_duration=0;    //否则无效不进行定时
		     timing_enable = 0;    //定时功能关闭
		}
}
void timing_startCount(void)
{
		if(timing_enable)
			++cur_timer;  //计数器计时 以秒为单位，在秒中断回调函数中运用

}
void tming_parameter_save(void)
{
    //u8  preTimer = readTimingParam();   //从FLASH读取定时参数
	  //if(preTimer != timing_duration)
    //     saveTimingParam(timing_duration);
		
		if(timing_duration >0 && timing_duration <= TIMING_VALUE_MAX)  //定时值在1-8小时内有效
			   timing_enable = 1;    //定时功能开启
		else  
		{  
			   timing_duration=0;    //否则无效不进行定时
		     timing_enable = 0;    //定时功能关闭
		}
}
//功能说明
//返回参数 0:表示定时时间未到，或定时功能没有开启
//        1:表法定时时间到了
u8  timing_run(void)
{
	  u8 var;

		if(si_level == 0 || timing_enable==0)  //当档位是0时定时重新启动
		{
		    cur_timer = 0;
			  if(si_level == 0)
					  timing_duration =0;
			  return 0;
		}
		var = (u8)(cur_timer / 3600);
		
		if(var >= timing_duration)
			return 1;
		
		return 0;
		
}
static u8 readTimingParam(void)
{
	  u32   tmp;
	  u32  *dirDat = (u32 *)FLASH_USER_START_ADDR;
	  u8    res=0,var;
	
    for(u8 i=0;i<sizeof(DATA)/4;i++)
	  {
		    tmp = *dirDat;//VarA.arrA[i]; //
			  dirDat++;
			  //putchar(tmp);
			  if(i==1)
				{
				    res = (u8)tmp;
					  /*var = (u8)(tmp>>8);
					  if(res == (~var))
							return res;
						else
							return 0;*/
					  break;
				}
		}
    return res;

}
static void saveTimingParam(u8 timer)
{
    u32   tmp = ~timer;
	  
	  tmp <<= 8;
	  tmp  += timer;
	  DATA[1] = tmp;
	  data_save_flash(DATA,sizeof(DATA),FLASH_USER_START_ADDR);
	
   
}

