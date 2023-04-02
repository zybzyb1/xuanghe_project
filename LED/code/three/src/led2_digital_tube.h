#ifndef  LED2_DIGITAL_TUBE_H
#define  LED2_DIGITAL_TUBE_H

#include	"type_def.h"		
#include  "intrins.h"	//使用nop()函数需引用此文件
 
extern u8  digital_value[2];
extern u8  led_display_enable;

extern void  led_display(void);


#endif




