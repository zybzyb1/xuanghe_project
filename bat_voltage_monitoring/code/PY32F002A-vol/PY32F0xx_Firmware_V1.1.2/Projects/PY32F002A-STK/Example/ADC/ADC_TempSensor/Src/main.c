/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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
#include "led2_digital_tube.h"
#include "encryptionDecryption.h"
#include "temperature.h"
#include "user_gpio.h"
#include "user_flash.h"
#include  "rerst_io_pin.h"
#include "led.h"

/* Private define ------------------------------------------------------------*/
#define Vcc_Power     3.3l                                            /* VCC电源电压,根据实际情况修改 */
#define TScal1        (float)((HAL_ADC_TSCAL1) * 3.3 / Vcc_Power)     /* 85摄氏度校准值对应电压*/
#define TScal2        (float)((HAL_ADC_TSCAL2) * 3.3 / Vcc_Power)     /* 30摄氏度校准值对应电压 */
#define TStem1        30l                                             /* 30摄氏度*/
#define TStem2        85l                                             /* 85摄氏度 */
#define Temp_k        ((float)(TStem2-TStem1)/(float)(TScal2-TScal1)) /* 温度计算 */
/* Private variables ---------------------------------------------------------*/
ADC_ChannelConfTypeDef        sConfig;
EXTI_HandleTypeDef   exti_handle;
TIM_HandleTypeDef    Tim16Handle;
TIM_HandleTypeDef    Tim1Handle;
IWDG_HandleTypeDef   IwdgHandle;

u8 run_secondFlag;
u8 ms8_flag;
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);
void APP_ADCConfig(void);

void Tim16_Configure(u16 DelayUs);    //配置定时器16--139us中断一次
void Tim1_Configure(void);  //配置定时器us --中断一次
void APP_SystemClockConfig(void);
void iwdg_init(void);
void rdelay_acton_fun(u8 action_value);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
	uint32_t ticks;
	
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();  
	
	/* 系统时钟配置 */
  APP_SystemClockConfig();

  APP_ADCConfig();

  /* 初始化调试串口(printf使用) */
  //BSP_USART_Config();
	 /* 打印调试信息 */
  //printf("print test");

  temperature_init();
	
	HAL_Delay(1000);
	val_get_deal();	
  HAL_Delay(2000);
	val_get_deal();	
  	//Tim16_Configure(1000);    //配置定时器16--139us中断一次
	Tim1_Configure();//配置定时器10ms --中断一次
	
	rerst_to_gpio();
	
  gpio_config();
		
	digital_display_init();
		
  led_init();
	
	iwdg_init();
	
  display_second=0;
	ms8_flag = 0;
  run_secondFlag = 0;
	 

#if 1
	/*喂狗*/
	if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)
	{
			Error_Handler();
	}
	code_run();

  ID:
	
  if(id_compare())
	{
	    /*喂狗*/
			if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)
			{
					Error_Handler();
			}
		  HAL_Delay(50);
		  goto ID;
	}	
#endif
	
  /* 无限循环 */
  while (1)
  {
	
		
#if LED_ENABLE	
		 led_run();
#endif
		 
		 val_get_deal();	
		if(ms8_flag)
		{
				ms8_flag=0;
				digital_run();	
		}			
		
  }
}

void Tim16_Configure(u16 DelayUs)    //配置定时器16--250us 139us中断一次
{
	 
		/* 定时器配置 */
		Tim16Handle.Instance = TIM16;                                          /* 选择TIM16 */
		Tim16Handle.Init.Period            = DelayUs-1;//139-1;                            /* 自动重装载值 */
	  Tim16Handle.Init.Prescaler         = 8 - 1;                            /* 预分频为8-1 */  //系统时钟为8M 8分频后 1us累加一次
		Tim16Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* 时钟不分频 */
		Tim16Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* 向上计数 */
		Tim16Handle.Init.RepetitionCounter = 1 - 1;                            /* 不重复计数 每个周期都产生中断的意思*/
		Tim16Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; //TIM_AUTORELOAD_PRELOAD_ENABLE;//  /* 自动重装载寄存器没有缓冲 */
		if (HAL_TIM_Base_Init(&Tim16Handle) != HAL_OK)                         /* TIM16初始化 */
		{
			Error_Handler();
		}
		//Tim16Handle.Instance->EGR &= ~TIM_EGR_UG;
		
#if 1
		if (HAL_TIM_Base_Start_IT(&Tim16Handle) != HAL_OK)                     /* TIM16使能启动，并使能中断*/
		{
			Error_Handler();
		}
#endif
}
void Tim1_Configure(void)     //配置定时器 MS --中断一次
{
  
		Tim1Handle.Instance = TIM1;                                           /* 选择TIM1 */
		Tim1Handle.Init.Period            = 7000-1; //delayus - 1;            /* 自动重装载值 */
		Tim1Handle.Init.Prescaler         = 8 - 1;                            /* 预分频为8-1 */   //1us累加一次
		Tim1Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* 时钟不分频 */
		Tim1Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* 向上计数 */
		Tim1Handle.Init.RepetitionCounter = 1 - 1;                            /* 不重复计数 */
		Tim1Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;    // TIM_AUTORELOAD_PRELOAD_DISABLE;   /* 自动重装载寄存器没有缓冲 */
		if (HAL_TIM_Base_Init(&Tim1Handle) != HAL_OK)                         /* TIM1初始化 */
		{
			Error_Handler();
		}

		if (HAL_TIM_Base_Start_IT(&Tim1Handle) != HAL_OK)                     /* TIM1使能启动，并使能中断 */
		{
			/* Starting Error */
			Error_Handler();
		}

}
/**
  * @brief  TIM执行函数，TIM1更新中断后翻转LED
  * @param  无
  * @retval 无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	  static u8 sendCnt=0;
	
    if(htim->Instance == TIM1)  //8ms中断一次
		{ 
						sendCnt++;
            secFlag =1;
			      ms8_flag = 1;
					  //digital_run();
							 
					  if(sendCnt == 13)   //91ms
						{
							   ++display_second; 
                 sendCnt =0;		
                /*喂狗*/
								if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)
								{
										Error_Handler();
								}							
						}
						/*if(sendCnt == 200)     //1s
						{
						    sendCnt = 0;
							 
						}*/
			
		}
		else if(htim->Instance == TIM16)
		{

		}
			
} 
void HAL_TIMEx_BreakCallback(TIM_HandleTypeDef *htim)
{
	  if(htim->Instance == TIM16)
		{
			  printf("TIM16-BreakCall");
		}
    else if(htim->Instance == TIM1)
		{
		    printf("TIM1-BreakCall"); 
			  
		} 
}
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM16)
		{
				printf("TIM16-CommutCall");
		}
		else if(htim->Instance == TIM1)
		{
		     
			  printf("TIM1-CommutCall");
		}
}


//GPIO所有引脚电平中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
}
/**
  * @brief  过零检测中断入口函数，每产生一次下降沿,过零一次
  * @param  无
  * @retval 无
  */
void EXTI4_15_IRQHandler(void)
{
    
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);         /* 处理EXTI中断请求 */
}

/**
  * @brief  中断入口函数，每产生一次中断切换下次边沿中断类型
  * @param  无
  * @retval 无
  */

void EXTI2_3_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);         /* 处理EXTI中断请求 */

}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
void APP_ADCConfig(void)
{
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_ENABLE();                                                     /* 使能ADC时钟 */

  AdcHandle.Instance = ADC1;
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)                          /* ADC校准 */
  {
    Error_Handler();
  }
  AdcHandle.Instance                   = ADC1;                                    /* ADC*/
  AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV1;                /* 模拟ADC时钟源为PCLK*/
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 转换分辨率12bit*/
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* 数据右对齐 */
  AdcHandle.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;              /* 扫描序列方向：向上(从通道0到通道11)*/
  AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* 转换结束标志*/  //ADC_EOC_SEQ_CONV
  AdcHandle.Init.LowPowerAutoWait      = ENABLE;                                  /* 等待转换模式开启 */
  AdcHandle.Init.ContinuousConvMode    = DISABLE;                                 /* 单次转换模式 */
  AdcHandle.Init.DiscontinuousConvMode = ENABLE;                                  /* 不使能非连续模式 */ //DISABLE;
  AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;                      /* 软件触发 */
  AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;           /* 触发边沿无 */
  AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* 当过载发生时，覆盖上一个值*/
  AdcHandle.Init.SamplingTimeCommon    = ADC_SAMPLETIME_41CYCLES_5;               /* 通道采样时间为41.5ADC时钟周期 */
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)                                         /* ADC初始化*/
  {
    Error_Handler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                                 /* 设置是否排行, 想设置单通道采样,需配置ADC_RANK_NONE */
  sConfig.Channel      = ADC_CHANNEL_TEMPSENSOR;                                  /* 设置采样通道 */
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)                      /* 配置ADC通道 */
  {
    Error_Handler();
  }

}

void  iwdg_init(void)
{
		IwdgHandle.Instance = IWDG;                     /* 选择IWDG */
		IwdgHandle.Init.Prescaler = IWDG_PRESCALER_32;  /* 配置32分频 */
		IwdgHandle.Init.Reload = (300);                /* IWDG计数器重装载值为500,0.5s. 1000，1s */

		if (HAL_IWDG_Init(&IwdgHandle) != HAL_OK)        /* 初始化IWDG */
		{

			Error_Handler();
		}

}

/**
  * @brief  ADC转换完成执行函数,打印当前测得得温度值
  * @param  无
  * @retval 无
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	
	//int16_t  aTEMPERATURE;
	
  aADCxConvertedData  = hadc->Instance->DR;
  //aTEMPERATURE =(int16_t)(Temp_k * aADCxConvertedData - Temp_k * TScal1 + TStem1);
  //printf(" TEMPERAUTE=%d \r\n", aADCxConvertedData);//aTEMPERATURE);
	
	ad_done_flag = 1;

}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* 振荡器配置 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI; /* 选择振荡器HSE,HSI,LSI */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                          /* 开启HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                          /* HSI 1分频 */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz; /* 配置HSI时钟8MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                         /* 关闭HSE */
  /*RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;*/
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;                         /* 关闭LSI */

  /* 配置振荡器 */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* 时钟源配置 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* 选择配置时钟 HCLK,SYSCLK,PCLK1 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;         /* 选择HSI作为系统时钟 */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;             /* AHB时钟 1分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;              /* APB时钟 1分频 */
  /* 配置时钟源 */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void)
{
  /* 无限循环 */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  输出产生断言错误的源文件名及行号
  * @param  file：源文件名指针
  * @param  line：发生断言错误的行号
  * @retval 无
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* 用户可以根据需要添加自己的打印信息,
     例如: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* 无限循环 */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
