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

#include	"STC8G_H_ADC.h"

#ifdef  ADC_TIMER_ENABLE	

//========================================================================
// ����: void	ADC_Inilize(ADC_InitTypeDef *ADCx)
// ����: ADC��ʼ������.
// ����: ADCx: �ṹ����,��ο�adc.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void	ADC_Inilize(ADC_InitTypeDef *ADCx)
{
	ADCCFG = (ADCCFG & ~ADC_SPEED_2X16T) | ADCx->ADC_Speed;	//����ADC����ʱ��Ƶ��
	ADC_Justify(ADCx->ADC_AdjResult);		//ADת��������뷽ʽ

	if(ADCx->ADC_SMPduty > 31)	return;	//����
	if(ADCx->ADC_CsSetup > 1)	return;	//����
	if(ADCx->ADC_CsHold > 3)	return;	//����

	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	ADCTIM = (ADCx->ADC_CsSetup << 7) | (ADCx->ADC_CsHold << 5) | ADCx->ADC_SMPduty ;		//���� ADC �ڲ�ʱ��ADC����ʱ�佨�������ֵ
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}


//========================================================================
// ����: void	ADC_PowerControl(u8 pwr)
// ����: ADC��Դ���Ƴ���.
// ����: pwr: ��Դ����,ENABLE��DISABLE.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void	ADC_PowerControl(u8 pwr)
{
	if(pwr == ENABLE)	ADC_CONTR |= 0x80;
	else				ADC_CONTR &= 0x7f;
}

//========================================================================
// ����: u16	Get_ADCResult(u8 channel)
// ����: ��ѯ����һ��ADCת�����.
// ����: channel: ѡ��Ҫת����ADCͨ��.
// ����: ADCת�����.
// �汾: V1.0, 2012-10-22
//========================================================================
u16	Get_ADCResult(u8 channel)	//channel = 0~15
{
	u16	adc;
	u8	i;

	if(channel > ADC_CH15)	return	4096;	//����,����4096,���õĳ����ж�	
	ADC_RES = 0;
	ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xf0) | ADC_START | channel; 
	NOP(4);			//��ADC_CONTR������Ҫ4T֮����ܷ���

	for(i=0; i<250; i++)		//��ʱ
	{
		if(ADC_CONTR & ADC_FLAG)
		{
			ADC_CONTR &= ~ADC_FLAG;
			if(ADCCFG &  (1<<5))		//ת������Ҷ��롣 
			{
				adc = ((u16)ADC_RES << 8) | ADC_RESL;
			}
			else		//ת���������롣 
			{
				#if ADC_RES_12BIT==1
					adc = (u16)ADC_RES;
					adc = (adc << 4) | ((ADC_RESL >> 4)&0x0f);
				#else
					adc = (u16)ADC_RES;
					adc = (adc << 2) | ((ADC_RESL >> 6)&0x03);
				#endif
			}
			return	adc;
		}
	}
	return	4096;	//����,����4096,���õĳ����ж�
}
#endif