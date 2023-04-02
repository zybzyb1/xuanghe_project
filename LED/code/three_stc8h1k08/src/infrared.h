#ifndef   _INFRARED_H
#define   _INFRARED_H

#include	"type_def.h"		
#include  "intrins.h"	//使用nop()函数需引用此文件

#define  IR_DATA_BUFFER_SIZE  10
#define  IR_ONOFF_BUTTON     0xBB    //红外摇控板开关键值
#define  IR_LIGHT_BUTTON     0x1B    //红外摇控板加热丝档位调整键值

#define  BUTTON_VALUE_MAX     4   //按键最大次数是4第5次触摸归0

extern u8 btn_value;
extern u8 IR_time;		  //下降沿之间的时间计数值
extern u32 time_cnt;   //定时计数器 计数单位1s


void infrared_check_deal(void);
void infrared_init(void);

#endif


