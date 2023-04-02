#include  "timing.h"
#include  "global.h"
#include "user_flash.h"
#include "py32f002xx_Start_Kit.h"
#include  "infrared.h"

u8   timing_enable;     //��ʱʹ�ܱ�־
u8   timing_duration;   //��ʱʱ��
u32  cur_timer;         //��ʱ������ ����Ϊ��λ


static u8 readTimingParam(void);
static void saveTimingParam(u8 timer);

void timing_init(void)
{
    cur_timer = 0;
	#if 0 
    timing_duration = readTimingParam();   //��FLASH��ȡ��ʱ����
	  if(timing_duration >0 && timing_duration <= TIMING_VALUE_MAX)  //��ʱֵ��1-8Сʱ����Ч
			   timing_enable = 1;    //��ʱ���ܿ���	
		else  
	#endif
		{  
			   timing_duration=0;    //������Ч�����ж�ʱ
		     timing_enable = 0;    //��ʱ���ܹر�
		}
}
void timing_startCount(void)
{
		if(timing_enable)
			++cur_timer;  //��������ʱ ����Ϊ��λ�������жϻص�����������

}
void tming_parameter_save(void)
{
    //u8  preTimer = readTimingParam();   //��FLASH��ȡ��ʱ����
	  //if(preTimer != timing_duration)
    //     saveTimingParam(timing_duration);
		
		if(timing_duration >0 && timing_duration <= TIMING_VALUE_MAX)  //��ʱֵ��1-8Сʱ����Ч
			   timing_enable = 1;    //��ʱ���ܿ���
		else  
		{  
			   timing_duration=0;    //������Ч�����ж�ʱ
		     timing_enable = 0;    //��ʱ���ܹر�
		}
}
//����˵��
//���ز��� 0:��ʾ��ʱʱ��δ������ʱ����û�п���
//        1:����ʱʱ�䵽��
u8  timing_run(void)
{
	  u8 var;

		if(si_level == 0 || timing_enable==0)  //����λ��0ʱ��ʱ��������
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

