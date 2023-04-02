#include  "rerst_io_pin.h"
#include  "py32f0xx_hal.h"

void rerst_to_gpio(void)
{
	  FLASH_OBProgramInitTypeDef OBInitCfg;
                                        
	  if( READ_BIT(FLASH->OPTR, FLASH_OPTR_NRST_MODE) == 0)
	  {
		 HAL_FLASH_Unlock();                                 /* 解锁FLASH */
		 HAL_FLASH_OB_Unlock();                              /* 解锁FLASH OPTION  */

		 OBInitCfg.OptionType = OPTIONBYTE_USER;
		 OBInitCfg.USERType = OB_USER_BOR_EN | OB_USER_BOR_LEV | OB_USER_IWDG_SW | OB_USER_NRST_MODE;// | OB_USER_nBOOT1;
		 /* BOR不使能/BOR上升3.2,下降3.1/软件模式看门狗/RST改为GPIO/System memory作为启动区 */
		 OBInitCfg.USERConfig = OB_BOR_DISABLE | OB_BOR_LEVEL_3p1_3p2 | OB_IWDG_SW |  OB_RESET_MODE_GPIO | OB_BOOT1_SYSTEM;
		 /* 启动option byte编程 */
		 HAL_FLASH_OBProgram(&OBInitCfg);
		 HAL_FLASH_Lock();                                   /* 锁定FLASH */
		 HAL_FLASH_OB_Lock();                                /* 锁定FLASH OPTION */
		 /* 产生一个复位，option byte装载 */
		 HAL_FLASH_OB_Launch();
	  }
}

