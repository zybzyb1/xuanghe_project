#ifndef  LED2_DIGITAL_TUBE_H
#define  LED2_DIGITAL_TUBE_H

#include	"global.h"
 
extern u8  shine_enable;       //通道2显示闪烁使能
extern u8  digital_value[2];   //通道1显示数据缓冲区
extern u8  led_display_chang;
extern u8  timDisplay_value[2];//通道2显示数据缓冲区
extern u16 display_second;     //通道2显示秒计时器
extern void  led_display(void);
extern void  led_display_init(void);

#endif




