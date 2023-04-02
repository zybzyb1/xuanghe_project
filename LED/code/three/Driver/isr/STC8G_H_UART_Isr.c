
#include "STC8G_H_UART.h"
#include "uart.h"
//========================================================================
// ����: UART1_ISR_Handler
// ����: UART1�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
#ifdef UART1
void UART1_ISR_Handler (void) interrupt UART1_VECTOR
{
	if(RI)
	{
		  RI = 0;

		  if(uart_revLen >= UART1_BUF_SIZE)
				 uart_revLen = 0;
			
			uart_rev[uart_revLen] = SBUF;
			++uart_revLen;
	
			uart_time=0;
		
		 
	}

	if(TI)
	{
		 TI = 0;
		 busy = 0; 
	}
}
#endif

//========================================================================
// ����: UART2_ISR_Handler
// ����: UART2�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
#ifdef UART2
void UART2_ISR_Handler (void) interrupt UART2_VECTOR
{
	if(RI2)
	{
		CLR_RI2();
		#if 0
		if(COM2.B_RX_OK == 0)
		{
			if(COM2.RX_Cnt >= COM_RX2_Lenth)	COM2.RX_Cnt = 0;
			RX2_Buffer[COM2.RX_Cnt++] = S2BUF;
			COM2.RX_TimeOut = TimeOutSet2;
		}
		#endif
	}

	if(TI2)
	{
		CLR_TI2();
//		COM2.B_TX_busy = 0;
		
//		if(COM2.TX_read != COM2.TX_write)
//		{
//		 	S2BUF = TX2_Buffer[COM2.TX_read];
//			if(++COM2.TX_read >= COM_TX2_Lenth)		COM2.TX_read = 0;
//		}
//		else	COM2.B_TX_busy = 0;
	}
}
#endif

//========================================================================
// ����: UART3_ISR_Handler
// ����: UART3�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
#ifdef UART3
void UART3_ISR_Handler (void) interrupt UART3_VECTOR
{
	if(RI3)
	{
		CLR_RI3();
		if(COM3.B_RX_OK == 0)
		{
			if(COM3.RX_Cnt >= COM_RX3_Lenth)	COM3.RX_Cnt = 0;
			RX3_Buffer[COM3.RX_Cnt++] = S3BUF;
			COM3.RX_TimeOut = TimeOutSet3;
		}
	}

	if(TI3)
	{
		CLR_TI3();
		COM3.B_TX_busy = 0;
		
//		if(COM3.TX_read != COM3.TX_write)
//		{
//		 	S3BUF = TX3_Buffer[COM3.TX_read];
//			if(++COM3.TX_read >= COM_TX3_Lenth)		COM3.TX_read = 0;
//		}
//		else	COM3.B_TX_busy = 0;
	}
}
#endif

//========================================================================
// ����: UART4_ISR_Handler
// ����: UART4�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
#ifdef UART4
void UART4_ISR_Handler (void) interrupt UART4_VECTOR
{
	if(RI4)
	{
		CLR_RI4();
		if(COM4.B_RX_OK == 0)
		{
			if(COM4.RX_Cnt >= COM_RX4_Lenth)	COM4.RX_Cnt = 0;
			RX4_Buffer[COM4.RX_Cnt++] = S4BUF;
			COM4.RX_TimeOut = TimeOutSet4;
		}
	}

	if(TI4)
	{
		CLR_TI4();
		COM4.B_TX_busy = 0;
		
//		if(COM4.TX_read != COM4.TX_write)
//		{
//		 	S4BUF = TX4_Buffer[COM4.TX_read];
//			if(++COM4.TX_read >= COM_TX4_Lenth)		COM4.TX_read = 0;
//		}
//		else	COM4.B_TX_busy = 0;
	}
}
#endif