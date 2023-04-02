#ifndef   _STC8G1K_CODE_H
#define   _STC8G1K_CODE_H


#include	"global.h"


//函数声明
void delay(u16 count);		//延时函数声明
void Time0_Handler_Callback(void); 	//任务标记回调函数
void Time1_Handler_Callback(void);	//任务标记回调函数
void rdelay_acton_fun(u8 action_value);
void display_para(u8 bak);

#endif


