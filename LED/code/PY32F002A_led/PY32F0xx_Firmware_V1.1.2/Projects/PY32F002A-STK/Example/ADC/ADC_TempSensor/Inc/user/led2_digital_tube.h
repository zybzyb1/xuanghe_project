#ifndef  LED2_DIGITAL_TUBE_H
#define  LED2_DIGITAL_TUBE_H

#include	"global.h"
 
extern u8  shine_enable;       //ͨ��2��ʾ��˸ʹ��
extern u8  digital_value[2];   //ͨ��1��ʾ���ݻ�����
extern u8  led_display_chang;
extern u8  timDisplay_value[2];//ͨ��2��ʾ���ݻ�����
extern u16 display_second;     //ͨ��2��ʾ���ʱ��
extern void  led_display(void);
extern void  led_display_init(void);

#endif




