#include  "rerst_io_pin.h"
#include  "py32f0xx_hal.h"

void rerst_to_gpio(void)
{
	  FLASH_OBProgramInitTypeDef OBInitCfg;
                                        
	  if( READ_BIT(FLASH->OPTR, FLASH_OPTR_NRST_MODE) == 0)
	  {
		 HAL_FLASH_Unlock();                                 /* ����FLASH */
		 HAL_FLASH_OB_Unlock();                              /* ����FLASH OPTION  */

		 OBInitCfg.OptionType = OPTIONBYTE_USER;
		 OBInitCfg.USERType = OB_USER_BOR_EN | OB_USER_BOR_LEV | OB_USER_IWDG_SW | OB_USER_NRST_MODE;// | OB_USER_nBOOT1;
		 /* BOR��ʹ��/BOR����3.2,�½�3.1/���ģʽ���Ź�/RST��ΪGPIO/System memory��Ϊ������ */
		 OBInitCfg.USERConfig = OB_BOR_DISABLE | OB_BOR_LEVEL_3p1_3p2 | OB_IWDG_SW |  OB_RESET_MODE_GPIO | OB_BOOT1_SYSTEM;
		 /* ����option byte��� */
		 HAL_FLASH_OBProgram(&OBInitCfg);
		 HAL_FLASH_Lock();                                   /* ����FLASH */
		 HAL_FLASH_OB_Lock();                                /* ����FLASH OPTION */
		 /* ����һ����λ��option byteװ�� */
		 HAL_FLASH_OB_Launch();
	  }
}

