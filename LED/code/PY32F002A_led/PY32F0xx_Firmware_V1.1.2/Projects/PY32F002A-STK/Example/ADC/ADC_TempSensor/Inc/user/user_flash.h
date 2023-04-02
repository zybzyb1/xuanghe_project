#ifndef  _FLASH_H
#define  _FLASH_H

#include  "global.h"

//0x0800 0000-0x0800 FFFF 64KBytes Main flash memory
//
/* Private define ------------------------------------------------------------*/
#define FLASH_USER_START_ADDR     0x08004000   //16K
/* Private variables ---------------------------------------------------------*/
typedef struct
{
  u32 arrA[32];
} NewDataType;                                                      /* �ṹ�嶨�� */
#define VarA (*(volatile NewDataType *)FLASH_USER_START_ADDR)       /* Flash�洢��ַ���� */


extern u32 DATA[32];
extern void  data_save_flash(u32 *dat,u16 len,u32 startAddr);



#endif

