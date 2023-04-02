#include "user_gpio.h"
#include  "py32f0xx_hal.h"

ADC_HandleTypeDef             AdcHandle;


void adc_enable(void)
{
    if (HAL_ADC_Start_IT(&AdcHandle) != HAL_OK)                                      /*ADC开启，并且开启中断*/
		{
			Error_Handler();
		}
}

u8 read_touch(void)
{
    u8 res;
    res = HAL_GPIO_ReadPin(TOUCH_GPIO_PORT,TOUCH_PIN)==GPIO_PIN_RESET ? 0 : 1;
    return res;
}
//1、翻转  0、置1
void buzzer_driver(u8 type)
{
	  if(type == 1)  //翻转
			  HAL_GPIO_TogglePin(BUZZER_GPIO_PORT, BUZZER_PIN);   /* LED翻转 */
		else 
			  HAL_GPIO_WritePin(BUZZER_GPIO_PORT,BUZZER_PIN, GPIO_PIN_SET); //置1
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
	#if 1
	  /* Configure the led两位数码管 pin */
	  GPIO_InitStruct.Pin = DIGITAL_DATA_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(DIGITAL_DATA_GPIO_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(DIGITAL_DATA_GPIO_PORT,DIGITAL_DATA_PIN, GPIO_PIN_RESET);
		
		GPIO_InitStruct.Pin = DIGITAL_DIG1_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(DIGITAL_DIG_PORT, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = DIGITAL_DIG2_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(DIGITAL_DIG_PORT, &GPIO_InitStruct);
		
		HAL_GPIO_WritePin(DIGITAL_DIG_PORT,DIGITAL_DIG1_PIN | DIGITAL_DIG2_PIN, GPIO_PIN_RESET);
	#endif	
		/* Configure the buzzer pin蜂鸣器 */
		GPIO_InitStruct.Pin = BUZZER_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(BUZZER_GPIO_PORT,BUZZER_PIN, GPIO_PIN_SET);
		
		/* Configure the N Check pin过零检测引脚 */
    GPIO_InitStruct.Pin = N_CHECK_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  //GPIO_InitStruct.Alternate = DEBUG_USART_RX_AF;
    HAL_GPIO_Init(N_CHECK_GPIO_PORT, &GPIO_InitStruct);
		
		 /* Configure the 可控硅控制 pin */
	  GPIO_InitStruct.Pin = SI_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(SI_GPIO_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(SI_GPIO_PORT,SI_PIN, GPIO_PIN_RESET);
}

