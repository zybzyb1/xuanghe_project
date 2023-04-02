#include "user_gpio.h"
#include  "py32f0xx_hal.h"

u8 read_touch(void)
{
    u8 res;
    res = HAL_GPIO_ReadPin(TOUCH_GPIO_PORT,TOUCH_PIN)==GPIO_PIN_RESET ? 0 : 1;
    return res;
}
void buzzer_driver(u8 type)
{
	  if(type == 1)  //·­×ª
			  HAL_GPIO_TogglePin(BUZZER_GPIO_PORT, BUZZER_PIN);   /* LED·­×ª */
		else 
			  HAL_GPIO_WritePin(BUZZER_GPIO_PORT,BUZZER_PIN, GPIO_PIN_SET); //ÖÃ1
}
 

void gpio_config(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

		/* Enable the GPIO Clock */
		__HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOF_CLK_ENABLE();
	
		/* Configure the touch pin */
		GPIO_InitStruct.Pin = TOUCH_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  //GPIO_InitStruct.Alternate = DEBUG_USART_RX_AF;
    HAL_GPIO_Init(TOUCH_GPIO_PORT, &GPIO_InitStruct);
	
	  /* Configure the ledÁ½Î»LEDµÆ pin */
	  GPIO_InitStruct.Pin = RED_PIN|GREEN_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(RED_GPIO_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(RED_GPIO_PORT,GREEN_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(RED_GPIO_PORT,RED_PIN, GPIO_PIN_RESET);
		
		GPIO_InitStruct.Pin = LIGHT_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(LIGHT_GPIO_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(LIGHT_GPIO_PORT,LIGHT_PIN, GPIO_PIN_RESET);
		
		/* Configure the buzzer pin·äÃùÆ÷ */
		GPIO_InitStruct.Pin = BUZZER_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(BUZZER_GPIO_PORT,BUZZER_PIN, GPIO_PIN_SET);
		
		/* Configure the¼ÌµçÆ÷1Òý½Å */
    GPIO_InitStruct.Pin = DELAY1_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  //GPIO_InitStruct.Alternate = DEBUG_USART_RX_AF;
    HAL_GPIO_Init(DELAY1_GPIO_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(DELAY1_GPIO_PORT,DELAY1_PIN, GPIO_PIN_RESET);
		
		/* Configure the¼ÌµçÆ÷1Òý½Å */
    GPIO_InitStruct.Pin = DELAY2_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  //GPIO_InitStruct.Alternate = DEBUG_USART_RX_AF;
    HAL_GPIO_Init(DELAY2_GPIO_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(DELAY2_GPIO_PORT,DELAY2_PIN, GPIO_PIN_RESET);
}

