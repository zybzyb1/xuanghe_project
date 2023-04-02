#include "user_flash.h"
#include "py32f0xx_hal.h"
#include "main.h"


u32 DATA[32] = {     0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
                     0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
                     0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
                     0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
                    };

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_FlashErase(u32 startAddr,u16 len);
static void APP_FlashProgram(u32 *dat,u16 len,u32 startAddr);
static void APP_FlashBlank(u32 startAddr,u16 len);
static void APP_FlashVerify(u32 *dat,u16 len,u32 startAddr);
										
										
/**
  * @brief  擦除FLASH
  * @param  len 是字节长度
  * @retval 无
  */
static void APP_FlashErase(u32 startAddr,u16 len)
{
  u32 PAGEError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct;

  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGEERASE;         /* 擦写类型FLASH_TYPEERASE_PAGEERASE=Page擦, FLASH_TYPEERASE_SECTORERASE=Sector擦 */
  EraseInitStruct.PageAddress = startAddr;//FLASH_USER_START_ADDR;             /* 擦写起始地址 */
  EraseInitStruct.NbPages  = len / FLASH_PAGE_SIZE;       /* 需要擦写的页数量 */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)   /* 执行page擦除,PAGEError返回擦写错误的page,返回0xFFFFFFFF,表示擦写成功 */
  {
    Error_Handler();
  }
}
/**
  * @brief  写FLASH
  * @param  len 是字节长度
  * @retval 无
  */
static void APP_FlashProgram(u32 *dat,u16 len,u32 startAddr)
{
  u32 flash_program_start = startAddr;//FLASH_USER_START_ADDR ;                                /* flash写起始地址 */
  u32 flash_program_end = (startAddr + len);//(FLASH_USER_START_ADDR + len);                           /* flash写结束地址 */
  u32 *src = dat;                                                                  /* 数组指针 */

  while (flash_program_start < flash_program_end)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src) == HAL_OK)  /* 执行Program */
    {
      flash_program_start += FLASH_PAGE_SIZE;                                           /* flash起始指针指向第一个page */
      src += FLASH_PAGE_SIZE / 4;                                                       /* 更新数据指针 */
    }
  }
}
/**
  * @brief  查空FLASH
  * @param  len 是字节长度
  * @retval 无
  */
static void APP_FlashBlank(u32 startAddr,u16 len)
{
  u32 addr = 0;

  while (addr < len)
  {
    if (0xFFFFFFFF != HW32_REG(startAddr + addr))
    {
      Error_Handler();
    }
    addr +=4;
  }
}
/**
  * @brief  校验FLASH
  * @param  len 是字节长度
  * @retval 无
  */
static void APP_FlashVerify(u32 *dat,u16 len,u32 startAddr)
{
  u32 addr = 0;

  while (addr < len)
  {
    if (dat[addr/4] != HW32_REG(startAddr + addr))
    {
      Error_Handler();
    }
    addr+=4;
  }
}
/**
  * @brief  保存数据到FLASH
  * @param  dat指向数据的指针，len 是字节长度
  * @retval 无
  */
void  data_save_flash(u32 *dat,u16 len,u32 startAddr)
{
/*解锁FLASH*/
  HAL_FLASH_Unlock();

  /*擦除FLASH*/
  APP_FlashErase(startAddr,len);

  /*查空FLASH*/
  APP_FlashBlank(startAddr,len);

  /*写FLASH*/
  APP_FlashProgram(dat,len,startAddr);

  /*锁定FLASH*/
  HAL_FLASH_Lock();

  /*校验FLASH*/
  APP_FlashVerify(dat,len,startAddr);
}

