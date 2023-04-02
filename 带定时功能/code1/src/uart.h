#ifndef    _UART_H
#define   _UART_H

#include  "STC8xxxx.h"
#include "intrins.h"
#include "global.h"

#ifdef UART_ENABLE

#define  UART1_BUF_SIZE   30
struct  comx_define
{ 
	u8	id;				//串口号

	u8	TX_read;		//发送读指针
	u8	TX_write;		//发送写指针
	u8	B_TX_busy;		//忙标志

	u8 	RX_Cnt;			//接收字节计数
	u8	RX_TimeOut;		//接收超时
	u8	B_RX_OK;		//接收块完成
}; 
#define  COMx_Define  struct  comx_define
//typedef 
struct  com_initdefine
{ 
	u8	UART_Mode;			//模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	u8	UART_BRT_Use;		//使用波特率,   BRT_Timer1,BRT_Timer2
	u32	UART_BaudRate;		//波特率,       ENABLE,DISABLE
	u8	Morecommunicate;	//多机通讯允许, ENABLE,DISABLE
	u8	UART_RxEnable;		//允许接收,   ENABLE,DISABLE
	u8	BaudRateDouble;		//波特率加倍, ENABLE,DISABLE
	u8	UART_Interrupt;		//中断控制,   ENABLE,DISABLE
	u8	UART_Polity;		//优先级,     PolityLow,PolityHigh
	u8	UART_P_SW;			//切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
};
#define  COMx_InitDefine  struct  com_initdefine 


extern void UartInit();
//extern void  sendData(void);
//extern void UartSend(char dat);
extern void PrintString1(u8 *puts);
extern void TX1_write2buff(u8 dat);

#define  UART1 1
//#define  UART2 2


#define	UART_ShiftRight	0		//同步移位输出
#define	UART_8bit_BRTx	(1<<6)	//8位数据,可变波特率
#define	UART_9bit		(2<<6)	//9位数据,固定波特率
#define	UART_9bit_BRTx	(3<<6)	//9位数据,可变波特率

#define	TimeOutSet1		5
#define	TimeOutSet2		5
#define	TimeOutSet3		5
#define	TimeOutSet4		5

#define	UART1_SW_P30_P31	0
#define	UART1_SW_P36_P37	(1<<6)
#define	UART1_SW_P16_P17	(2<<6)
#define	UART1_SW_P43_P44	(3<<6)
#define	UART2_SW_P10_P11	0
#define	UART2_SW_P46_P47	1
#define	UART3_SW_P00_P01	0
#define	UART3_SW_P50_P51	2
#define	UART4_SW_P02_P03	0
#define	UART4_SW_P52_P53	4

#define	BRT_Timer1	1
#define	BRT_Timer2	2
#define	BRT_Timer3	3
#define	BRT_Timer4	4


#endif
#endif
