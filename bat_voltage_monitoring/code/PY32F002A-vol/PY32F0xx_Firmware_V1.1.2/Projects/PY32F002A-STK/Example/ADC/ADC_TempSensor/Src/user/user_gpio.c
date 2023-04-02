#include "user_gpio.h"
#include  "py32f0xx_hal.h"

ADC_HandleTypeDef             AdcHandle;

extern void Error_Handler(void);

void adc_enable(void)
{
    if (HAL_ADC_Start_IT(&AdcHandle) != HAL_OK)                                      /*ADC开启，并且开启中断*/
		{
			Error_Handler();
		}
}


 

void gpio_config(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

		/* Enable the GPIO Clock */
		__HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOF_CLK_ENABLE();
	

	  /* Configure the  3位数码管 pin */
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
		HAL_GPIO_Init(DIGITAL_DIG1_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(DIGITAL_DIG1_PORT,DIGITAL_DIG1_PIN , GPIO_PIN_RESET);
		
		GPIO_InitStruct.Pin = DIGITAL_DIG2_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(DIGITAL_DIG2_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(DIGITAL_DIG2_PORT,DIGITAL_DIG2_PIN, GPIO_PIN_RESET);

	  GPIO_InitStruct.Pin = DIGITAL_DIG3_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(DIGITAL_DIG3_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(DIGITAL_DIG3_PORT,DIGITAL_DIG3_PIN, GPIO_PIN_RESET);
		
		 /* Configure the DP pin */
	  GPIO_InitStruct.Pin = DP_DATA_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(DP_DATA_GPIO_PORT, &GPIO_InitStruct);		
		HAL_GPIO_WritePin(DP_DATA_GPIO_PORT,DP_DATA_PIN, GPIO_PIN_RESET);
	 ;

#if LED_ENABLE		
	   /* Configure the DP pin */
	  GPIO_InitStruct.Pin = LED_RED|LED_GREEN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(LED_GPIO_PORT,LED_RED|LED_GREEN, GPIO_PIN_RESET);
		
#endif
}

