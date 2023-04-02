#ifndef  TEMPERATURE_H
#define  TEMPERATURE_H

#include	"global.h"		

extern u8 secFlag;       //秒标志
extern u16 aADCxConvertedData;
extern u8 ad_done_flag;  //ADC转换完成标志
extern u16  vol_value;
extern u8   vol_enable;
extern u8 firstcnt;
extern void temperature_init(void);
extern void val_get_deal(void);


#endif


