#ifndef  _TIMEING_H
#define  _TIMEING_H

#include  "global.h"

#define   TIMING_VALUE_MAX   8


extern u8   timing_enable;     //��ʱʹ�ܱ�־
extern u8   timing_duration; //��ʱʱ��
//extern u32  cur_timer;       //��ʱ������ ����Ϊ��λ

extern void timing_init(void);
extern void timing_startCount(void);//��ʱ������ ����Ϊ��λ
extern u8  timing_run(void);
extern void tming_parameter_save(void);

#endif

