/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU       PY32F002AW1556TV
  * @brief   Main program body
  * @date
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "buzzer.h"
#include "infrared.h"
#include "encryptionDecryption.h"
#include "touch.h"
#include "user_gpio.h"
#include "user_flash.h"


/* Private variables ---------------------------------------------------------*/
//ADC_HandleTypeDef             AdcHandle;
//ADC_ChannelConfTypeDef        sConfig;
EXTI_HandleTypeDef   exti_handle;
TIM_HandleTypeDef    Tim16Handle;
TIM_HandleTypeDef    Tim1Handle;
IWDG_HandleTypeDef   IwdgHandle;


/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);
//void APP_ADCConfig(void);
void Configure_EXTI_N_Check(void);
void Configure_EXTI_Ir(uint8_t type/*0下沿中断，1上沿中断*/);
void Tim16_Configure(void);    //配置定时器16--139us中断一次
void Tim1_Configure(u16 timeUs);  //配置定时器us --中断一次
void APP_SystemClockConfig(void);
void iwdg_init(void);
void rdelay_acton_fun(u8 action_value);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();  
	
	/* 系统时钟配置 */
  APP_SystemClockConfig();

  /* 初始化调试串口(printf使用) */
  //BSP_USART_Config();

	Configure_EXTI_Ir(0 /*0下沿中断，1上沿中断*/);
	Tim16_Configure();    //配置定时器16--139us中断一次
	iwdg_init();	

  gpio_config();
  infrared_init(); //红外初始化函数
	touch_init();    //触摸初始化函数
	buzzer_init();
  rdelay_acton_fun(0);
	
  code_run();
#if  1	
  ID:
  if(id_compare())
	{
	    /*喂狗*/
			if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)
			{
					Error_Handler();
			}
		  HAL_Delay(100);
		  goto ID;
	}	
#endif
	
  /* 无限循环 */
  while (1)
  {
		 /*喂狗*/
    if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)
    {
				Error_Handler();
    }

		 infrared_check_deal(); 
		 touch_check_deal();//触摸检测
     buzzer_run();

  }
}
void Tim16_Configure(void)    //配置定时器16--250us 139us中断一次
{
	 
		/* 定时器配置 */
		Tim16Handle.Instance = TIM16;                                          /* 选择TIM16 */
		Tim16Handle.Init.Period            = 250-1;//139-1;                            /* 自动重装载值 */
	  Tim16Handle.Init.Prescaler         = 8 - 1;                            /* 预分频为8-1 */  //系统时钟为8M 8分频后 1us累加一次
		Tim16Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* 时钟不分频 */
		Tim16Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* 向上计数 */
		Tim16Handle.Init.RepetitionCounter = 1 - 1;                            /* 不重复计数 */
		Tim16Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;//TIM_AUTORELOAD_PRELOAD_DISABLE;   /* 自动重装载寄存器没有缓冲 */
		if (HAL_TIM_Base_Init(&Tim16Handle) != HAL_OK)                         /* TIM16初始化 */
		{
			Error_Handler();
		}

		if (HAL_TIM_Base_Start_IT(&Tim16Handle) != HAL_OK)                     /* TIM16使能启动，并使能中断*/
		{
			Error_Handler();
		}

}
void Tim1_Configure(u16 delayus)     //配置定时器 MS --中断一次
{
  
		Tim1Handle.Instance = TIM1;                                           /* 选择TIM1 */
		Tim1Handle.Init.Period            = delayus - 1;                      /* 自动重装载值 */
		Tim1Handle.Init.Prescaler         = 8 - 1;                            /* 预分频为8-1 */   //1us累加一次
		Tim1Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* 时钟不分频 */
		Tim1Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* 向上计数 */
		Tim1Handle.Init.RepetitionCounter = 1 - 1;                            /* 不重复计数 */
		Tim1Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* 自动重装载寄存器没有缓冲 */
		if (HAL_TIM_Base_Init(&Tim1Handle) != HAL_OK)                         /* TIM1初始化 */
		{
			Error_Handler();
		}
#if 0
		if (HAL_TIM_Base_Start_IT(&Tim1Handle) != HAL_OK)                     /* TIM1使能启动，并使能中断 */
		{
			/* Starting Error */
			Error_Handler();
		}
#endif
}
/**
  * @brief  TIM执行函数，TIM1更新中断后翻转LED
  * @param  无
  * @retval 无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	  static u8 ms10Cnt=0;
	  static u8 sendCnt=0;
	
    if(htim->Instance == TIM16)  //250us中断一次
		{
			  buzzer_io_driver();  //蜂鸣器驱动
			
			  if(++ms10Cnt == 20)      //5ms
				{	
						ms10Cnt = 0;
					  if(++sendCnt == 25)  //125ms
						{
					      sendCnt =0;
							  buzzer_timer++;
						}
				}
			  
			  if(IR_time < 0xfc)
						IR_time++;
	
				Touch_time++;

			
		}
		else if(htim->Instance == TIM1)
		{
		    
	      //SI_ON();   //开启可控硅
			  //delay(10);  //延时2us
        //SI_OFF();  //关断可控硅 
		
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
	  //u16  timeVal;// 0x0662; // 0x04c9; //0x1327;
	
    if(GPIO_Pin == IR_PIN)
		{  //红外接收引脚中断
			
		    if(ir_int_flag==1)
				{   //是上升沿中断
						 ir_rising();  //红外上沿处理      
				}
				else
				{
						//是下降沿中断
						 ir_falling();  //红外下沿处理
				}
		 
		}

}
/**
  * @brief  过零检测中断入口函数，每产生一次下降沿,过零一次
  * @param  无
  * @retval 无
  */
void EXTI4_15_IRQHandler(void)
{
    
    //HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);         /* 处理EXTI中断请求 */
}
/**
  * @brief  配置过零检测外部中断引脚
  * @param  无
  * @retval 无
  */
void Configure_EXTI_N_Check(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  __HAL_RCC_GPIOA_CLK_ENABLE();                   /* 使能GPIOA时钟 */
  GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;   /* GPIO模式为下降沿中断 */
  GPIO_InitStruct.Pull  = GPIO_PULLUP;            /* 上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;   /* 速度为高速 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);                /* 使能EXTI中断 */
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);        /* 配置中断优先级 */
}


/**
  * @brief  中断入口函数，每产生一次中断切换下次边沿中断类型
  * @param  无
  * @retval 无
  */

void EXTI2_3_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(IR_PIN);         /* 处理EXTI中断请求 */
	if(ir_int_flag==1)
	{   //是上升沿中断
	    Configure_EXTI_Ir(0);/* 配置GPIO模式为下降沿中断 */  
	}
	else
	{
		  //是下降沿中断
		  Configure_EXTI_Ir(1); /* 配置GPIO模式为上沿中断 */
	}
}

/**
  * @brief  配置过零检测外部中断引脚
  * @param  无
  * @retval 无
  */
void Configure_EXTI_Ir(uint8_t type/*0下沿中断，1上沿中断*/)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  __HAL_RCC_GPIOA_CLK_ENABLE();                    /* 使能GPIOB时钟 */
	if(type == 0)
	{
			GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;/* GPIO模式为下降沿中断 */
		  ir_int_flag=0;
	}
	else
	{
		  GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;   /* GPIO模式为上沿中断 */
		  ir_int_flag=1;
	}
  GPIO_InitStruct.Pull  = GPIO_PULLUP;           /* 上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;    /* 速度为高速 */
  GPIO_InitStruct.Pin = IR_PIN;
  HAL_GPIO_Init(IR_GPIO_PORT, &GPIO_InitStruct);
	
  HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);                /* 使能EXTI中断 */
  HAL_NVIC_SetPriority(EXTI2_3_IRQn, 0, 1);        /* 配置中断优先级 */
}
#if 0
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
  AdcHandle.Init.EOCSelection          = ADC_EOC_SEQ_CONV;                        /* 转换结束标志*/
  AdcHandle.Init.LowPowerAutoWait      = ENABLE;                                  /* 等待转换模式开启 */
  AdcHandle.Init.ContinuousConvMode    = DISABLE;                                 /* 单次转换模式 */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                                 /* 不使能非连续模式 */
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
#endif
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
#if 0
/**
  * @brief  ADC转换完成执行函数,打印当前测得得温度值
  * @param  无
  * @retval 无
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  aADCxConvertedData = hadc->Instance->DR;
  //aTEMPERATURE =(int16_t)(Temp_k * aADCxConvertedData - Temp_k * TScal1 + TStem1);
  printf(" TEMPERAUTE=%d \r\n", aADCxConvertedData);//aTEMPERATURE);
	
}
#endif
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
void rdelay_acton_fun(u8 action_value)
{
	#if 1
	  buzzerEnableFlag = 1;
	  if(method_res_compare())
		  action_value = 6;
		
    switch(action_value)
		{
		    case 0:  // 断开所有继电器
					  DELAY1_OFF();  //上电LED数码管不显示
				    DELAY2_OFF(); 
				    RED_ON();
				    GREEN_OFF();
				    LIGHT_OFF(); 
				    sysFunFlag = 0; 
        break;
				case 1:    
				    DELAY1_ON();  //
				    DELAY2_OFF(); 
        break;
				case 2:  //
				    DELAY1_OFF();  //
				    DELAY2_ON(); 
        break;
				case 3: 
				    DELAY1_ON();  //
				    DELAY2_ON(); 
        break;
				case 4: 
				    DELAY1_ON();  //
				    DELAY2_ON();
				    LIGHT_ON();
        break;
				case 5:  //
				    DELAY1_OFF();
				    DELAY2_OFF();
				    LIGHT_ON();
        break;
				case 6:  //数码管显示1E
				    LIGHT_OFF();
				    sysFunFlag = 0;  
            DELAY1_OFF();
				    DELAY2_OFF();
				    RED_ON();
				    GREEN_OFF();
        break;
		    default:
					
				break;
		}
#endif
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
