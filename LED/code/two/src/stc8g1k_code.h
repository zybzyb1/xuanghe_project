#ifndef   _STC8G1K_CODE_H
#define   _STC8G1K_CODE_H

/*
题外话：因半导体价格涨幅较大和国外形势，开始考虑尽量使用国产芯片（支持国货），先从单片机开始，目前暂定要求不高的场合选择应用较多的STC系列，其中STC8G和STC8H系列为STC主推的型号。
注：程序大部分来源于网络，并做了较大幅度的修改，原因是不是用于红外数据传输，而是作为光电开关来用。
      参考NEC编码做了简化,便于延长发射管寿命。
      发射管为IR204、接收头为IRM-H638T/TR2、单片机为STC8G1K08A。
原文链接：https://blog.csdn.net/tsliuch/article/details/112554696
*/

#include	"type_def.h"		
#include  "intrins.h"	//使用nop()函数需引用此文件
 
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

#define IR_SENDDATA 0x05    //红外发射的数据

//函数声明
void delay(u16 count);		//延时函数声明
void Time0_Handler_Callback(void); 	//任务标记回调函数
void Time1_Handler_Callback(void);	//任务标记回调函数
void rdelay_acton_fun(u8 action_value);
void display_para(u8 bak);
#endif


