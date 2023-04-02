#ifndef  TEMPERATURE_H
#define  TEMPERATURE_H

#include	"type_def.h"		
#include  "intrins.h"	//使用nop()函数需引用此文件

extern bit secFlag;       //秒标志
extern bit overtemperature_flag;

extern void temperature_init(void);
extern void temperature_get_deal(void);
extern u8 overtemperature_check(void);

#endif

 