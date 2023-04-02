#ifndef   _INFRARED_H
#define   _INFRARED_H

#include	"global.h"		


#define  IR_DATA_BUFFER_SIZE  10
#define  IR_ONOFF_BUTTON     0x1B    //红外摇控板开关键值
#define  IR_LIGHT_BUTTON     0xBB    //红外摇控板加热丝档位调整键值

#define  BUTTON_VALUE_MAX     3   //按键最大次数是4第5次触摸归0

extern u8 sysFunFlag;      //系统功能标志
extern u8 btn_value;
extern u8 IR_time;		     //下降沿之间的时间计数值
extern u32 time_cnt;       //定时计数器 计数单位1s
extern u8 ir_int_flag;     //红外中断边沿类型
extern u8 si_level;
extern u8 timing_enableFlag;

extern void infrared_check_deal(void);
extern void infrared_init(void);
extern void ir_falling(void);  //红外下沿处理
extern void ir_rising(void);  //红外上沿处理
#endif


