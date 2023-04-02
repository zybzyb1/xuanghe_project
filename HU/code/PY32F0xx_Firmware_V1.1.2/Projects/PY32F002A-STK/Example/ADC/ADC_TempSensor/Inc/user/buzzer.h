#ifndef  _BUZZER_H
#define  _BUZZER_H

#include	"global.h"		


extern u8 buzzerEnableFlag;
extern u8 buzzer_timer;


extern void buzzer_init(void);
extern void buzzer_run(void);
extern void buzzer_time_set(u8 time);
extern void buzzer_io_driver(void);
#endif


