#ifndef  TEMPERATURE_H
#define  TEMPERATURE_H

#include	"global.h"		

extern u8 secFlag;       //秒标志
extern u8 overtemperature_flag;
extern u16 aADCxConvertedData;
extern u8 ad_done_flag;  //ADC转换完成标志

extern void temperature_init(void);
extern void temperature_get_deal(void);
extern u8 overtemperature_check(void);

#endif


