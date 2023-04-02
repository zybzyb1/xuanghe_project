#include "buzzer.h"
#include "global.h"
#include "STC8xxxx.h"

bit buzzerEnableFlag;

u8 buzzer_timer;
u8 buzzer_config_time;

static void to_PWM_value(u8 pwm_val);
static void pwm0_init(void);
void buzzer_time_set(u8 time);

void buzzer_init(void)
{
    buzzerEnableFlag =1;
	  pwm0_init();
	  to_PWM_value(0x7f);  //蜂鸣器驱动脉冲频率2000
	  buzzer_time_set(2);  //250ms 
}

void buzzer_run(void)
{
    if(buzzerEnableFlag)
		{
			  buzzerEnableFlag = 0;
			  buzzer_timer =0;
			  to_PWM_value(0x7f);  //蜂鸣器驱动脉冲频率2000
			  PCA_PWM0 = 0;
			  CR = 1; //启动 PCA 计时器
		}
    else
		{
		    if(buzzer_timer > buzzer_config_time)  //计时单位125ms
				{
				     buzzer_timer = 0;
					   CR = 0; //停止 PCA 计时器 
             PCA_PWM0 &= 0xC0;
             CCAP0H = 0x00;  //PWM 固定输出高电平				
				}
		}

}

void PWM0_Isr() interrupt PWM0_VECTOR
{
		if (PWMCFG01 & 0x08)
		{
				PWMCFG01 &= ~0x08; //清中断标志
		 
		}
}
void buzzer_time_set(u8 time)
{
    buzzer_config_time = time;
}
static void pwm0_init(void)
{

	P_SW1 &= ~0x18;  //pwm波形从p1.1端口输出
	CCON = 0x00;
	CMOD = 0x80; //PCA 时钟为系统时钟12/1 0x08; //PCA 时钟为系统时钟
	CL = 0x00;
	CH = 0x00;
	
	CCAPM0 = 0x42; //PCA 模块 0 为 PWM 工作模式
	PCA_PWM0 = 0;//0x70/0x80 //PCA 模块 0 输出 8/7/6 位 PWM   6  10.5us  7  21.2us  8 42.5us  0.5ms
	CCAP0L = 0x7f; //比较值 PWM 占空比为 50%[(40H-20H)/40H]
	CCAP0H = 0x7f;  //重载值 
	/*
	CCAPM1 = 0x42; //PCA 模块 1 为 PWM 工作模式
	PCA_PWM1 = 0x40; //PCA 模块 1 输出 7 位 PWM
	CCAP1L = 0x20; //PWM 占空比为 75%[(80H-20H)/80H]
	CCAP1H = 0x20;
	
	CCAPM2 = 0x42; //PCA 模块 2 为 PWM 工作模式
	PCA_PWM2 = 0x00; //PCA 模块 2 输出 8 位 PWM
	CCAP2L = 0x20; //PWM 占空比为 87.5%[(100H-20H)/100H]
	CCAP2H = 0x20;
	*/
	//CR = 1; //启动 PCA 计时器
	
		
}

//*************************************
// 函数名称：TOPWMVALUE
// 函数功能：设置PWM占空比
// 入口参数：占空比值
// 出口参数：无
//***************************************
void to_PWM_value(u8 pwm_val) 
{
		 
		CCAP0L = pwm_val;//pwm_percentage;
	  CCAP0H = pwm_val;//pwm_percentage;
	  
}