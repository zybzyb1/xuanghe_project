#include	"type_def.h"
#include "intrins.h"
#include "uart.h"
#include "STC8xxxx.h"

#ifdef UART_ENABLE

#define  FOSC  6000000UL//11059200UL //
#define  BRT  (65536 - FOSC / 9600 / 4)

#ifdef UART1
#define	COM_TX1_Lenth	30
#define	COM_RX1_Lenth	30
#endif

volatile  bit busy;

#ifdef UART1
COMx_Define	COM1;
u8	xdata TX1_Buffer[COM_TX1_Lenth];	//���ͻ���
u8 	xdata RX1_Buffer[COM_RX1_Lenth];	//���ջ���
#endif

u8 UART_Configuration(u8 UARTx, COMx_InitDefine *COMx)
{
	u8	i;
	u32	j;
	
#ifdef UART1
	if(UARTx == UART1)
	{
		COM1.id = 1;
		COM1.TX_read    = 0;
		COM1.TX_write   = 0;
		COM1.B_TX_busy  = 0;
		COM1.RX_Cnt     = 0;
		COM1.RX_TimeOut = 0;
		COM1.B_RX_OK    = 0;
		for(i=0; i<COM_TX1_Lenth; i++)	TX1_Buffer[i] = 0;
		for(i=0; i<COM_RX1_Lenth; i++)	RX1_Buffer[i] = 0;

		if(COMx->UART_Polity > Polity_3)	return 2;	//����
		UART1_Polity(COMx->UART_Polity);	//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
		if(COMx->UART_Mode > UART_9bit_BRTx)	return 2;	//ģʽ����
		SCON = (SCON & 0x3f) | COMx->UART_Mode;
		if((COMx->UART_Mode == UART_9bit_BRTx) || (COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{
			j = (FOSC / 4) / COMx->UART_BaudRate;	//��1T����
			if(j >= 65536UL)	return 2;	//����
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer1)
			{
				TR1 = 0;
				AUXR &= ~0x01;		//S1 BRT Use Timer1;
				TMOD &= ~(1<<6);	//Timer1 set As Timer
				TMOD &= ~0x30;		//Timer1_16bitAutoReload;
				AUXR |=  (1<<6);	//Timer1 set as 1T mode
				TH1 = (u8)(j>>8);
				TL1 = (u8)j;
				ET1 = 0;	//��ֹ�ж�
				TMOD &= ~0x40;	//��ʱ
				INT_CLKO &= ~0x02;	//�����ʱ��
				TR1  = 1;
			}
			else if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				AUXR &= ~(1<<4);	//Timer stop
				AUXR |= 0x01;		//S1 BRT Use Timer2;
				AUXR &= ~(1<<3);	//Timer2 set As Timer
				AUXR |=  (1<<2);	//Timer2 set as 1T mode
				TH2 = (u8)(j>>8);
				TL2 = (u8)j;
				IE2  &= ~(1<<2);	//��ֹ�ж�
				AUXR |=  (1<<4);	//Timer run enable
			}
			else return 2;	//����
		}
		else if(COMx->UART_Mode == UART_ShiftRight)
		{
			if(COMx->BaudRateDouble == ENABLE)	AUXR |=  (1<<5);	//�̶�������SysClk/2
			else								AUXR &= ~(1<<5);	//�̶�������SysClk/12
		}
		else if(COMx->UART_Mode == UART_9bit)	//�̶�������SysClk*2^SMOD/64
		{
			if(COMx->BaudRateDouble == ENABLE)	PCON |=  (1<<7);	//�̶�������SysClk/32
			else								PCON &= ~(1<<7);	//�̶�������SysClk/64
		}
		if(COMx->UART_Interrupt == ENABLE)	ES = 1;	//�����ж�
		else								ES = 0;	//��ֹ�ж�
		if(COMx->UART_RxEnable == ENABLE)	REN = 1;	//��������
		else								REN = 0;	//��ֹ����
		P_SW1 = (P_SW1 & 0x3f) | (COMx->UART_P_SW & 0xc0);	//�л�IO
		return	0;
	}
#endif
#ifdef UART2
	if(UARTx == UART2)
	{
		COM2.id = 2;
		COM2.TX_read    = 0;
		COM2.TX_write   = 0;
		COM2.B_TX_busy  = 0;
		COM2.RX_Cnt     = 0;
		COM2.RX_TimeOut = 0;
		COM2.B_RX_OK    = 0;
		for(i=0; i<COM_TX2_Lenth; i++)	TX2_Buffer[i] = 0;
		for(i=0; i<COM_RX2_Lenth; i++)	RX2_Buffer[i] = 0;

		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{
			if(COMx->UART_Polity > Polity_3)	return 2;	//����
			UART2_Polity(COMx->UART_Polity);	//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
			if(COMx->UART_Mode == UART_9bit_BRTx)	S2CON |=  (1<<7);	//9bit
			else									S2CON &= ~(1<<7);	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//��1T����
			if(j >= 65536UL)	return 2;	//����
			j = 65536UL - j;
			AUXR &= ~(1<<4);	//Timer stop
			AUXR &= ~(1<<3);	//Timer2 set As Timer
			AUXR |=  (1<<2);	//Timer2 set as 1T mode
			TH2 = (u8)(j>>8);
			TL2 = (u8)j;
			IE2  &= ~(1<<2);	//��ֹ�ж�
			AUXR |=  (1<<4);	//Timer run enable
		}
		else	return 2;	//ģʽ����
		if(COMx->UART_Interrupt == ENABLE)	IE2   |=  1;		//�����ж�
		else								IE2   &= ~1;		//��ֹ�ж�
		if(COMx->UART_RxEnable == ENABLE)	S2CON |=  (1<<4);	//��������
		else								S2CON &= ~(1<<4);	//��ֹ����
		P_SW2 = (P_SW2 & ~1) | (COMx->UART_P_SW & 0x01);	//�л�IO
		return	0;
	}
#endif
	
	return	2;	//����
}
void Uart1_Isr() interrupt 4
{
	u8 dat;
	#if 0
	if (TI)
	{
			TI = 0;
			busy = 0;
	}
	if (RI)
	{
			RI = 0;
		#if 0	
			if(uart_revLen >= UART1_BUF_SIZE)
				uart_revLen = 0;
			
			uart_rev[uart_revLen] = SBUF;
			++uart_revLen;
			uart_time=0;
		#endif
	}
	#endif
	
	if(RI)
	{
		RI = 0;

		if(COM1.B_RX_OK == 0)
		{
			//if(COM1.RX_Cnt >= COM_RX1_Lenth)	COM1.RX_Cnt = 0;
			//RX1_Buffer[COM1.RX_Cnt++] = SBUF;
			dat = SBUF;
			COM1.RX_TimeOut = TimeOutSet1;
		}
		
	}

	if(TI)
	{
		TI = 0;
		if(COM1.TX_read != COM1.TX_write)
		{
		 	SBUF = TX1_Buffer[COM1.TX_read];
			if(++COM1.TX_read >= COM_TX1_Lenth)		COM1.TX_read = 0;
		}
		else	COM1.B_TX_busy = 0;
	}
}

void TX1_write2buff(u8 dat)	//д�뷢�ͻ��壬ָ��+1
{
  while(COM1.B_TX_busy);
	TX1_Buffer[COM1.TX_write] = dat;	//װ���ͻ���
	if(++COM1.TX_write >= COM_TX1_Lenth)	COM1.TX_write = 0;

	if(COM1.B_TX_busy == 0)		//����
	{  
		COM1.B_TX_busy = 1;		//��־æ
		TI = 1;					//���������ж�
	}
}

void UartInit()
{
	#if 0
	/*SCON = 0x50;//0x5A;
	T2L = BRT;
	T2H = BRT >> 8;
	AUXR = 0x15;  //ok
	*/
	SCON = 0x50;
	//TMOD = 0x20;
	TL1 = BRT;
	TH1 = BRT >> 8;
	TR1 = 1;
	AUXR |= 0x40;
	busy = 0;
	
	//uart_revLen =0;
	//uart_sendLen=0;
	//uart_time=0;
	#endif
	
	
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 9600ul;			//������, һ�� 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = DISABLE;//ENABLE;				//��������,   ENABLE��DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
	COMx_InitStructure.UART_Interrupt = ENABLE;				//�ж�����,   ENABLE��DISABLE
	COMx_InitStructure.UART_Polity    = Polity_0;			//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
	COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
}
void PrintString1(u8 *puts)
{
    for (; *puts != 0;	puts++)  TX1_write2buff(*puts); 	//����ֹͣ��0����
}
#if 0
void UartSend(char dat)
{
	//while (!TI);
	//TI = 0;
	//SBUF = dat;
	while (busy);
	busy = 1;
	SBUF = dat;
}

void  sendData(void)
{
	u8 i=0;

	for(;i<uart_sendLen;i++)
		UartSend(uart_send[i]); 
	uart_sendLen=0;
}
#endif
#if 0
u8 revData()
{

		if(uart_revLen && uart_time>10)
				return uart_revLen;
	
		if(uart_time  > 20)
	  {
			 uart_revLen = 0;
			 uart_time =0;
	  }
		return 0;
}

void uartDataDeal(u8 *revD,u8 len)
{
	  u8  L,cod;
    bit flag=1;
		
    uart_sendLen =  0;
		L = protocol_judge(revD,len);
    if(L == 0)return;
		
	  //IWDG_ReloadCounter();//????? 
		L = funAnalysis(revD,L,revD,&cod);
    if(L == 0)return;
		 
	  //IWDG_ReloadCounter();//????? 
    L = commandMerge1(uart_send,cod,revD,L);
		if(L == 0)return;	
		uart_sendLen = L;
}

void comm_data_deal()
{
	if(revData()==0)
		return;

	 //IWDG_ReloadCounter();//????? ??????????????,???
   uartDataDeal(uart_rev,uart_revLen);//??????
	 uart_revLen = 0;
   sendData();
	 
}
#endif

#endif