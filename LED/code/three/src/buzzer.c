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
	  to_PWM_value(0x7f);  //��������������Ƶ��2000
	  buzzer_time_set(2);  //250ms 
}

void buzzer_run(void)
{
    if(buzzerEnableFlag)
		{
			  buzzerEnableFlag = 0;
			  buzzer_timer =0;
			  to_PWM_value(0x7f);  //��������������Ƶ��2000
			  PCA_PWM0 = 0;
			  CR = 1; //���� PCA ��ʱ��
		}
    else
		{
		    if(buzzer_timer > buzzer_config_time)  //��ʱ��λ125ms
				{
				     buzzer_timer = 0;
					   CR = 0; //ֹͣ PCA ��ʱ�� 
             PCA_PWM0 &= 0xC0;
             CCAP0H = 0x00;  //PWM �̶�����ߵ�ƽ				
				}
		}

}

void PWM0_Isr() interrupt PWM0_VECTOR
{
		if (PWMCFG01 & 0x08)
		{
				PWMCFG01 &= ~0x08; //���жϱ�־
		 
		}
}
void buzzer_time_set(u8 time)
{
    buzzer_config_time = time;
}
static void pwm0_init(void)
{

	P_SW1 &= ~0x18;  //pwm���δ�p1.1�˿����
	CCON = 0x00;
	CMOD = 0x80; //PCA ʱ��Ϊϵͳʱ��12/1 0x08; //PCA ʱ��Ϊϵͳʱ��
	CL = 0x00;
	CH = 0x00;
	
	CCAPM0 = 0x42; //PCA ģ�� 0 Ϊ PWM ����ģʽ
	PCA_PWM0 = 0;//0x70/0x80 //PCA ģ�� 0 ��� 8/7/6 λ PWM   6  10.5us  7  21.2us  8 42.5us  0.5ms
	CCAP0L = 0x7f; //�Ƚ�ֵ PWM ռ�ձ�Ϊ 50%[(40H-20H)/40H]
	CCAP0H = 0x7f;  //����ֵ 
	/*
	CCAPM1 = 0x42; //PCA ģ�� 1 Ϊ PWM ����ģʽ
	PCA_PWM1 = 0x40; //PCA ģ�� 1 ��� 7 λ PWM
	CCAP1L = 0x20; //PWM ռ�ձ�Ϊ 75%[(80H-20H)/80H]
	CCAP1H = 0x20;
	
	CCAPM2 = 0x42; //PCA ģ�� 2 Ϊ PWM ����ģʽ
	PCA_PWM2 = 0x00; //PCA ģ�� 2 ��� 8 λ PWM
	CCAP2L = 0x20; //PWM ռ�ձ�Ϊ 87.5%[(100H-20H)/100H]
	CCAP2H = 0x20;
	*/
	//CR = 1; //���� PCA ��ʱ��
	
		
}

//*************************************
// �������ƣ�TOPWMVALUE
// �������ܣ�����PWMռ�ձ�
// ��ڲ�����ռ�ձ�ֵ
// ���ڲ�������
//***************************************
void to_PWM_value(u8 pwm_val) 
{
		 
		CCAP0L = pwm_val;//pwm_percentage;
	  CCAP0H = pwm_val;//pwm_percentage;
	  
}