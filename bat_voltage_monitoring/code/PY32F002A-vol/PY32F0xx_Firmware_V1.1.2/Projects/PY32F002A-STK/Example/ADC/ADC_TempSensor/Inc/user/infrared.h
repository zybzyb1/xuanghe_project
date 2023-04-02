#ifndef   _INFRARED_H
#define   _INFRARED_H

#include	"global.h"		


#define  IR_DATA_BUFFER_SIZE  10
#define  IR_ONOFF_BUTTON     0x1B    //����ҡ�ذ忪�ؼ�ֵ
#define  IR_LIGHT_BUTTON     0xBB    //����ҡ�ذ����˿��λ������ֵ

#define  BUTTON_VALUE_MAX     3   //������������4��5�δ�����0

extern u8 sysFunFlag;      //ϵͳ���ܱ�־
extern u8 btn_value;
extern u8 IR_time;		     //�½���֮���ʱ�����ֵ
extern u32 time_cnt;       //��ʱ������ ������λ1s
extern u8 ir_int_flag;     //�����жϱ�������
extern u8 si_level;
extern u8 timing_enableFlag;

extern void infrared_check_deal(void);
extern void infrared_init(void);
extern void ir_falling(void);  //�������ش���
extern void ir_rising(void);  //�������ش���
#endif


