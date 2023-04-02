/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#ifndef __PWM_H
#define __PWM_H	 

#include	"config.h"

#define ENO1P       0x01
#define ENO1N       0x02
#define ENO2P       0x04
#define ENO2N       0x08
#define ENO3P       0x10
#define ENO3N       0x20
#define ENO4P       0x40
#define ENO4N       0x80

#define ENO5P       0x01
#define ENO6P       0x04
#define ENO7P       0x10
#define ENO8P       0x40

#define	PWM1	1
#define	PWM2	2
#define	PWM3	3
#define	PWM4	4
#define	PWM5	5
#define	PWM6	6
#define	PWM7	7
#define	PWM8	8

#define	PWMA	128
#define	PWMB	129

#define PWM_BIE     0x80
#define PWM_TIE     0x40
#define PWM_COMIE   0x20
#define PWM_CC4IE   0x10
#define PWM_CC3IE   0x08
#define PWM_CC2IE   0x04
#define PWM_CC1IE   0x02
#define PWM_CC8IE   0x10
#define PWM_CC7IE   0x08
#define PWM_CC6IE   0x04
#define PWM_CC5IE   0x02
#define PWM_UIE     0x01

typedef struct
{ 
	u8	PWM_Mode;			//ģʽ,   CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	u16	PWM_Period;		//����ʱ��,   0~65535
	u16	PWM_Duty;			//ռ�ձ�ʱ��, 0~Period
	u8	PWM_DeadTime;	//��������������, 0~255
//	u8	PWM_Reload;				//����Ƚϵ�Ԥװ��ʹ��,   ENABLE,DISABLE
//	u8	PWM_Fast;					//����ȽϿ��ٹ���ʹ��,   ENABLE,DISABLE
//	u8	PWM_PreLoad;			//Ԥװ��,     ENABLE,DISABLE
//	u8	PWM_BrakeEnable;	//ɲ������ʹ��,  ENABLE,DISABLE
	u8	PWM_EnoSelect;		//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	u8	PWM_CEN_Enable;		//ʹ�ܼ�����, ENABLE,DISABLE
	u8	PWM_MainOutEnable;//�����ʹ��,  ENABLE,DISABLE
} PWMx_InitDefine; 

typedef struct
{ 
	u16	PWM1_Duty;			//PWM1ռ�ձ�ʱ��, 0~Period
	u16	PWM2_Duty;			//PWM2ռ�ձ�ʱ��, 0~Period
	u16	PWM3_Duty;			//PWM3ռ�ձ�ʱ��, 0~Period
	u16	PWM4_Duty;			//PWM4ռ�ձ�ʱ��, 0~Period
	u16	PWM5_Duty;			//PWM5ռ�ձ�ʱ��, 0~Period
	u16	PWM6_Duty;			//PWM6ռ�ձ�ʱ��, 0~Period
	u16	PWM7_Duty;			//PWM7ռ�ձ�ʱ��, 0~Period
	u16	PWM8_Duty;			//PWM8ռ�ձ�ʱ��, 0~Period
} PWMx_Duty; 

u8	PWM_Configuration(u8 PWM, PWMx_InitDefine *PWMx);
void UpdatePwm(u8 PWM, PWMx_Duty *PWMx);

#endif

