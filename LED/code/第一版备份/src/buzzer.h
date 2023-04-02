#ifndef  _BUZZER_H
#define  _BUZZER_H

#include	"type_def.h"		
#include  "intrins.h"	//ʹ��nop()���������ô��ļ�

extern bit buzzerEnableFlag;
extern u8 buzzer_timer;


extern void buzzer_init(void);
extern void buzzer_run(void);
extern void buzzer_time_set(u8 time);

#endif


