#ifndef  TOUCH_H
#define  TOUCH_H

#include	"type_def.h"		
#include  "intrins.h"	//使用nop()函数需引用此文件

extern u16 Touch_time;      //触摸计时器

extern void  touch_check_deal(void);
extern void  touch_init(void);

#endif
