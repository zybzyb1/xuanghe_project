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
  * @brief  ����FLASH
  * @param  len ���ֽڳ���
  * @retval ��
  */
static void APP_FlashErase(u32 startAddr,u16 len)
{
  u32 PAGEError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct;

  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGEERASE;         /* ��д����FLASH_TYPEERASE_PAGEERASE=Page��, FLASH_TYPEERASE_SECTORERASE=Sector�� */
  EraseInitStruct.PageAddress = startAddr;//FLASH_USER_START_ADDR;             /* ��д��ʼ��ַ */
  EraseInitStruct.NbPages  = len / FLASH_PAGE_SIZE;       /* ��Ҫ��д��ҳ���� */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)   /* ִ��page����,PAGEError���ز�д�����page,����0xFFFFFFFF,��ʾ��д�ɹ� */
  {
    Error_Handler();
  }
}
/**
  * @brief  дFLASH
  * @param  len ���ֽڳ���
  * @retval ��
  */
static void APP_FlashProgram(u32 *dat,u16 len,u32 startAddr)
{
  u32 flash_program_start = startAddr;//FLASH_USER_START_ADDR ;                                /* flashд��ʼ��ַ */
  u32 flash_program_end = (startAddr + len);//(FLASH_USER_START_ADDR + len);                           /* flashд������ַ */
  u32 *src = dat;                                                                  /* ����ָ�� */

  while (flash_program_start < flash_program_end)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src) == HAL_OK)  /* ִ��Program */
    {
      flash_program_start += FLASH_PAGE_SIZE;                                           /* flash��ʼָ��ָ���һ��page */
      src += FLASH_PAGE_SIZE / 4;                                                       /* ��������ָ�� */
    }
  }
}
/**
  * @brief  ���FLASH
  * @param  len ���ֽڳ���
  * @retval ��
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
  * @brief  У��FLASH
  * @param  len ���ֽڳ���
  * @retval ��
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
  * @brief  �������ݵ�FLASH
  * @param  datָ�����ݵ�ָ�룬len ���ֽڳ���
  * @retval ��
  */
void  data_save_flash(u32 *dat,u16 len,u32 startAddr)
{
/*����FLASH*/
  HAL_FLASH_Unlock();

  /*����FLASH*/
  APP_FlashErase(startAddr,len);

  /*���FLASH*/
  APP_FlashBlank(startAddr,len);

  /*дFLASH*/
  APP_FlashProgram(dat,len,startAddr);

  /*����FLASH*/
  HAL_FLASH_Lock();

  /*У��FLASH*/
  APP_FlashVerify(dat,len,startAddr);
}

