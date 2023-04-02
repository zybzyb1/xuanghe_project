/**
  ******************************************************************************
  * @file    py32f0xx_hal_msp.c
  * @author  MCU Application Team
  * @brief   This file provides code for the MSP Initialization
  *          and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/**
  * @brief 初始化全局MSP
  */
void HAL_MspInit(void)
{
  //BSP_LED_Init(LED_GREEN);
	
	  /* 使能LSI时钟 */
  __HAL_RCC_LSI_ENABLE();

  /* 等待直到LSI READY置位 */
  while (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == 0U);

}

/**
  * @brief 初始化ADC相关MSP
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef          GPIO_InitStruct;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO clock ****************************************/
  __HAL_RCC_GPIOA_CLK_ENABLE();
  /* ADC1 Periph clock enable */
  __HAL_RCC_ADC_CLK_ENABLE();
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  /*##- 2- Configure peripheral GPIO #########################################*/
  /* ADC Channel GPIO pin configuration */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_NVIC_SetPriority(ADC_COMP_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(ADC_COMP_IRQn);
}
/**
  * @brief 初始化TIM16相关MSP
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  __HAL_RCC_TIM16_CLK_ENABLE();                          /* 使能TIM16时钟 */
  HAL_NVIC_SetPriority(TIM16_IRQn, 0, 0);                /* 设置中断优先级 */
  HAL_NVIC_EnableIRQ(TIM16_IRQn);                        /* 使能TIM16中断 */
	
	__HAL_RCC_TIM1_CLK_ENABLE();                            /* 使能TIM1时钟 */
  HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0, 0);   /* 设置中断优先级 */
  HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);           /* 使能TIM1中断 */
}


/**
  * @brief 初始化全局MSP
  */


/************************ (C) COPYRIGHT Puya *****END OF FILE****/
