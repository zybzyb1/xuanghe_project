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

#include	"STC8G_H_NVIC.h"
#include  "STC8G_H_ADC.h"
#include  "global.h"
//========================================================================
// ����: NVIC_Timer0_Init
// ����: Timer0Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_Timer0_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	Timer0_Interrupt(State);
	Timer0_Polity(Priority);
	return SUCCESS;
}

//========================================================================
// ����: NVIC_Timer1_Init
// ����: Timer1Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_Timer1_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	Timer1_Interrupt(State);
	Timer1_Polity(Priority);
	return SUCCESS;
}
#if 0
//========================================================================
// ����: NVIC_Timer2_Init
// ����: Timer2Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, NULL.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_Timer2_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	Timer2_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}

//========================================================================
// ����: NVIC_Timer3_Init
// ����: Timer3Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, NULL.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_Timer3_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	Timer3_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}

//========================================================================
// ����: NVIC_Timer4_Init
// ����: Timer4Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, NULL.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_Timer4_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	Timer4_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}

//========================================================================
// ����: NVIC_INT0_Init
// ����: INT0Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT0_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	INT0_Interrupt(State);
	INT0_Polity(Priority);
	return SUCCESS;
}

//========================================================================
// ����: NVIC_INT1_Init
// ����: INT1Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT1_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	INT1_Interrupt(State);
	INT1_Polity(Priority);
	return SUCCESS;
}

//========================================================================
// ����: NVIC_INT2_Init
// ����: INT2Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, NULL.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT2_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	INT2_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}

//========================================================================
// ����: NVIC_INT3_Init
// ����: INT3Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, NULL.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT3_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	INT3_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}

//========================================================================
// ����: NVIC_INT4_Init
// ����: INT4Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, NULL.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT4_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	INT4_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}
#endif
//========================================================================
// ����: NVIC_ADC_Init
// ����: ADCǶ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_ADC_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	ADC_Interrupt(State);
	ADC_Polity(Priority);
	return SUCCESS;
}
#if 0
//========================================================================
// ����: NVIC_CMP_Init
// ����: �Ƚ���Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, RISING_EDGE/FALLING_EDGE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_CMP_Init(u8 State, u8 Priority)
{
	if(State > RISING_EDGE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	if(State & RISING_EDGE)	CMPCR1 |= PIE;			//�����������ж�
	else	CMPCR1 &= ~PIE;			//��ֹ�������ж�
	if(State & FALLING_EDGE)	CMPCR1 |= NIE;		//�����½����ж�
	else	CMPCR1 &= ~NIE;			//��ֹ�������ж�
	CMP_Polity(Priority);
	return SUCCESS;
}

//========================================================================
// ����: NVIC_I2C_Init
// ����: I2CǶ�������жϿ�������ʼ��.
// ����: Mode:     ģʽ, I2C_Mode_Master/I2C_Mode_Slave.
// ����: State:    �ж�ʹ��״̬, I2C_Mode_Master: ENABLE/DISABLE.
//                              I2C_Mode_Slave: I2C_ESTAI/I2C_ERXI/I2C_ETXI/I2C_ESTOI/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_I2C_Init(u8 Mode, u8 State, u8 Priority)
{
	if(Mode > I2C_Mode_Master) return FAIL;
	if(Priority > Polity_3) return FAIL;
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	if(Mode == I2C_Mode_Master)
	{
		I2C_Master_Inturrupt(State);
	}
	else if(Mode == I2C_Mode_Slave)
	{
		I2CSLCR = (I2CSLCR & ~0x78) | State;
	}
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	CMP_Polity(Priority);
	return SUCCESS;
}
#endif
//========================================================================
// ����: NVIC_UART1_Init
// ����: UART1Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_UART1_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	UART1_Interrupt(State);
	UART1_Polity(Priority);
	return SUCCESS;
}

//========================================================================
// ����: NVIC_UART2_Init
// ����: UART2Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_UART2_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	UART2_Interrupt(State);
	UART2_Polity(Priority);
	return SUCCESS;
}
#if 0
//========================================================================
// ����: NVIC_UART3_Init
// ����: UART3Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_UART3_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	UART3_Interrupt(State);
	UART3_Polity(Priority);
	return SUCCESS;
}

//========================================================================
// ����: NVIC_UART4_Init
// ����: UART4Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_UART4_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	UART4_Interrupt(State);
	UART4_Polity(Priority);
	return SUCCESS;
}

//========================================================================
// ����: NVIC_SPI_Init
// ����: SPIǶ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_SPI_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Polity_3) return FAIL;
	SPI_Interrupt(State);
	SPI_Polity(Priority);
	return SUCCESS;
}
#endif
//========================================================================
// ����: NVIC_PWM_Init
// ����: PWMǶ�������жϿ�������ʼ��.
// ����: Channel:  ͨ��, PWM1/PWM2/PWM3/PWM4/PWM5/PWM6/PWM7/PWM8.
// ����: State:    �ж�ʹ��״̬, PWM_BIE/PWM_TIE/PWM_COMIE/PWM_CC8IE~PWM_CC1IE/PWM_UIE/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_PWM_Init(u8 Channel, u8 State, u8 Priority)
{
//	if(Channel > PWM8) return FAIL;
	if(Priority > Polity_3) return FAIL;
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	switch(Channel)
	{
		#if 0
		case PWM1:
			PWMA_IER = State;
			PWM1_Polity(Priority);
		break;

		case PWM2:
			PWMA_IER = State;
			PWM2_Polity(Priority);
		break;
   #endif
		case PWM3:
			PWMA_IER = State;
			PWM2_Polity(Priority);
		break;
   #if 0
		case PWM4:
			PWMA_IER = State;
			PWM2_Polity(Priority);
		break;

		case PWM5:
			PWMB_IER = State;
			PWM5_Polity(Priority);
		break;
    #endif
		default:
			PWMB_IER = State;
			Priority = NULL;
		  return FAIL;
		break;
	}
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	return SUCCESS;
}
#if 0
//========================================================================
// ����: NVIC_PCA_Init
// ����: PCAǶ�������жϿ�������ʼ��.
// ����: Channel:  ͨ��, PCA0/PCA1/PCA2/PCA_Counter.
// ����: State:    �ж�ʹ��״̬, PCA_ECOM/PCA_CCAPP/PCA_CCAPN/PCA_MAT/PCA_TOG/PCA_PWM/PCA_ECCF/DISABLE.
// ����: Priority: �ж����ȼ�, Polity_0,Polity_1,Polity_2,Polity_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_PCA_Init(u8 Channel, u8 State, u8 Priority)
{
	if(Channel > PCA_Counter) return FAIL;
	if(Priority > Polity_3) return FAIL;
	PCA_Polity(Priority);
	switch(Channel)
	{
		case PCA0:
			CCAPM0 = State;
		break;

		case PCA1:
			CCAPM1 = State;
		break;

		case PCA2:
			CCAPM2 = State;
		break;

		case PCA_Counter:
			CMOD = (CMOD  & ~1) | (State & 1);
		break;
	}
	return SUCCESS;
}

#endif