#ifndef   _INFRARED_H
#define   _INFRARED_H

#include	"type_def.h"		
#include  "intrins.h"	//ʹ��nop()���������ô��ļ�

#define  IR_DATA_BUFFER_SIZE  10
#define  IR_ONOFF_BUTTON     0xBB    //����ҡ�ذ忪�ؼ�ֵ
#define  IR_LIGHT_BUTTON     0x1B    //����ҡ�ذ����˿��λ������ֵ

#define  BUTTON_VALUE_MAX     4   //������������4��5�δ�����0

extern u8 btn_value;
extern u8 IR_time;		  //�½���֮���ʱ�����ֵ
extern u32 time_cnt;   //��ʱ������ ������λ1s


void infrared_check_deal(void);
void infrared_init(void);

#endif


