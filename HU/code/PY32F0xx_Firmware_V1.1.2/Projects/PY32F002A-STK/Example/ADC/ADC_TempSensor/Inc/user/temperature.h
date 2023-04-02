#ifndef  TEMPERATURE_H
#define  TEMPERATURE_H

#include	"global.h"		

extern u8 secFlag;       //√Î±Í÷æ
extern u8 overtemperature_flag;
extern u16 aADCxConvertedData;

extern void temperature_init(void);
extern void temperature_get_deal(void);
extern u8 overtemperature_check(void);

#endif


