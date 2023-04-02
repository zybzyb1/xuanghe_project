#ifndef  _TIMEING_H
#define  _TIMEING_H

#include  "global.h"

#define   TIMING_VALUE_MAX   8


extern u8   timing_enable;     //定时使能标志
extern u8   timing_duration; //定时时长
//extern u32  cur_timer;       //定时计数器 以秒为单位

extern void timing_init(void);
extern void timing_startCount(void);//定时计数器 以秒为单位
extern u8  timing_run(void);
extern void tming_parameter_save(void);

#endif

