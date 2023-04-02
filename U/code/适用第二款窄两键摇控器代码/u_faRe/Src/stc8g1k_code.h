#ifndef   _STC8G1K_CODE_H
#define   _STC8G1K_CODE_H

/*
���⻰����뵼��۸��Ƿ��ϴ�͹������ƣ���ʼ���Ǿ���ʹ�ù���оƬ��֧�ֹ��������ȴӵ�Ƭ����ʼ��Ŀǰ�ݶ�Ҫ�󲻸ߵĳ���ѡ��Ӧ�ý϶��STCϵ�У�����STC8G��STC8Hϵ��ΪSTC���Ƶ��ͺš�
ע������󲿷���Դ�����磬�����˽ϴ���ȵ��޸ģ�ԭ���ǲ������ں������ݴ��䣬������Ϊ��翪�����á�
      �ο�NEC�������˼�,�����ӳ������������
      �����ΪIR204������ͷΪIRM-H638T/TR2����Ƭ��ΪSTC8G1K08A��
ԭ�����ӣ�https://blog.csdn.net/tsliuch/article/details/112554696
*/

#include	"type_def.h"		
#include  "intrins.h"	//ʹ��nop()���������ô��ļ�
 
#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t

typedef unsigned char    uint8_t;
typedef unsigned int     uint16_t;
typedef unsigned long    uint32_t;
 
#define EX2 0x10
#define EX3 0x20
#define EX4 0x40

//280us @11.0592MHz
#define T1_START()  TL1 = 0xE7; \  
                    TH1 = 0xF3; \
                    ET1 = 1; \
			        TR1 = 1

#define IR_SENDDATA 0x05    //���ⷢ�������

//��������
void delay(u16 count);		//��ʱ��������
void Time0_Handler_Callback(void); 	//�����ǻص�����
void Time1_Handler_Callback(void);	//�����ǻص�����

#endif


