#ifndef  TEMPERATURE_H
#define  TEMPERATURE_H

#include	"type_def.h"		
#include  "intrins.h"	//ʹ��nop()���������ô��ļ�

extern bit secFlag;       //���־
extern bit overtemperature_flag;

extern void temperature_init(void);
extern void temperature_get_deal(void);
extern u8 overtemperature_check(void);

#endif

 