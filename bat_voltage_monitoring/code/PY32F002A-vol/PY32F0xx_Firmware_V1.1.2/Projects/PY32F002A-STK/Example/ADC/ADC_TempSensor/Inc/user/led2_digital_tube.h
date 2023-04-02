#ifndef  LED2_DIGITAL_TUBE_H
#define  LED2_DIGITAL_TUBE_H

#include	"global.h"
 
extern  u8  display_second;   //显示秒计时器
extern  u8  digital_value[3];   //显示数据缓冲区
extern  u8  percentage_reg;   //百分比
extern void  digital_run(void);
extern void  digital_display_init(void);

#endif




