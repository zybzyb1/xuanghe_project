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

#ifndef __UART_H
#define __UART_H	 

#include	"config.h"

//========================================================================
//                              UART����
//========================================================================

#define		UART1_Interrupt(n)	(n==0?(ES = 0):(ES = 1))					/* UART1�ж�ʹ�� */
#define		UART1_RxEnable(n)	(n==0?(REN = 0):(REN = 1))					/* UART1����ʹ�� */

#define		UART2_Interrupt(n)	IE2 = (IE2 & ~0x01) | (n)					/* UART2�ж�ʹ�� */
#define		UART2_RxEnable(n)	S2CON = (S2CON & ~0x10) | (n << 4)	/* UART2����ʹ�� */

#define		UART3_Interrupt(n)	IE2 = (IE2 & ~0x08) | (n << 3)		/* UART3�ж�ʹ�� */
#define		UART3_RxEnable(n)	S3CON = (S3CON & ~0x10) | (n << 4)	/* UART3����ʹ�� */

#define		UART4_Interrupt(n)	IE2 = (IE2 & ~0x10) | (n << 4)		/* UART4�ж�ʹ�� */
#define		UART4_RxEnable(n)	S4CON = (S4CON & ~0x10) | (n << 4)	/* UART4����ʹ�� */

//========================================================================
//                              ��������
//========================================================================

#define	UART1	1
#define	UART2	2
//#define	UART3	3
//#define	UART4	4

#ifdef UART1
#define	COM_TX1_Lenth	128
#define	COM_RX1_Lenth	128
#endif
#ifdef UART2
#define	COM_TX2_Lenth	16
#define	COM_RX2_Lenth	16
#endif
#ifdef UART3
#define	COM_TX3_Lenth	64
#define	COM_RX3_Lenth	64
#endif
#ifdef UART4
#define	COM_TX4_Lenth	32
#define	COM_RX4_Lenth	32
#endif

#define	UART_ShiftRight	0		//ͬ����λ���
#define	UART_8bit_BRTx	(1<<6)	//8λ����,�ɱ䲨����
#define	UART_9bit				(2<<6)	//9λ����,�̶�������
#define	UART_9bit_BRTx	(3<<6)	//9λ����,�ɱ䲨����


#define	TimeOutSet1		5
#define	TimeOutSet2		5
#define	TimeOutSet3		5
#define	TimeOutSet4		5

#define	BRT_Timer1	1
#define	BRT_Timer2	2
#define	BRT_Timer3	3
#define	BRT_Timer4	4

typedef struct
{ 
	u8	id;				//���ں�

	u8	TX_read;		//���Ͷ�ָ��
	u8	TX_write;		//����дָ��
	u8 B_TX_busy;		//æ��־

	u8 	RX_Cnt;			//�����ֽڼ���
	u8	RX_TimeOut;		//���ճ�ʱ
	u8	B_RX_OK;		//���տ����
} COMx_Define; 

typedef struct
{ 
	u8	UART_Mode;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	u8	UART_BRT_Use;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	u32	UART_BaudRate;		//������, 	   һ�� 110 ~ 115200
	u8	Morecommunicate;	//���ͨѶ����, ENABLE,DISABLE
	u8	UART_RxEnable;		//�������,   ENABLE,DISABLE
	u8	BaudRateDouble;		//�����ʼӱ�, ENABLE,DISABLE
} COMx_InitDefine; 

//extern	u8 xdata *TX1_Buffer;
//extern	u8 xdata *RX1_Buffer;
//extern	u8 xdata *TX2_Buffer;
//extern	u8 xdata *RX2_Buffer;
#if 0
#ifdef UART1
extern	COMx_Define	COM1;
extern	u8	xdata TX1_Buffer[COM_TX1_Lenth];	//���ͻ���
extern	u8 	xdata RX1_Buffer[COM_RX1_Lenth];	//���ջ���
#endif
#ifdef UART2
extern	COMx_Define	COM2;
extern	u8	xdata TX2_Buffer[COM_TX2_Lenth];	//���ͻ���
extern	u8 	xdata RX2_Buffer[COM_RX2_Lenth];	//���ջ���
#endif
#ifdef UART3
extern	COMx_Define	COM3;
extern	u8	xdata TX3_Buffer[COM_TX3_Lenth];	//���ͻ���
extern	u8 	xdata RX3_Buffer[COM_RX3_Lenth];	//���ջ���
#endif
#ifdef UART4
extern	COMx_Define	COM4;
extern	u8	xdata TX4_Buffer[COM_TX4_Lenth];	//���ͻ���
extern	u8 	xdata RX4_Buffer[COM_RX4_Lenth];	//���ջ���
#endif
#endif

u8	UART_Configuration(u8 UARTx, COMx_InitDefine *COMx);
#ifdef UART1
void TX1_write2buff(u8 dat);	//д�뷢�ͻ��壬ָ��+1
void PrintString1(u8 *puts);
#endif
#ifdef UART2
void TX2_write2buff(u8 dat);	//д�뷢�ͻ��壬ָ��+1
void PrintString2(u8 *puts);
#endif
#ifdef UART3
void TX3_write2buff(u8 dat);	//д�뷢�ͻ��壬ָ��+1
void PrintString3(u8 *puts);
#endif
#ifdef UART4
void TX4_write2buff(u8 dat);	//д�뷢�ͻ��壬ָ��+1
void PrintString4(u8 *puts);
#endif

//void COMx_write2buff(COMx_Define *COMx, u8 dat);	//д�뷢�ͻ��壬ָ��+1
//void PrintString(COMx_Define *COMx, u8 *puts);

#endif

