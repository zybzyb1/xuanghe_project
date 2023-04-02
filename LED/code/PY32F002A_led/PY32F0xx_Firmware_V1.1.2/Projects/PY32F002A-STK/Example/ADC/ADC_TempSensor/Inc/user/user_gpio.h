#ifndef  _USER_GPIO_H
#define  _USER_GPIO_H

#include  "global.h"
#include  "py32f0xx_hal.h"


#define TOUCH_PIN                           GPIO_PIN_3
#define TOUCH_GPIO_PORT                     GPIOB
 
#define DIGITAL_DATA_PIN                    GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
#define DIGITAL_DATA_GPIO_PORT              GPIOA

#define DIGITAL_DIG1_PIN                    GPIO_PIN_0
#define DIGITAL_DIG2_PIN                    GPIO_PIN_1
#define DIGITAL_DIG_PORT                    GPIOF

#define N_CHECK_PIN                         GPIO_PIN_7
#define N_CHECK_GPIO_PORT                   GPIOA

#define BUZZER_PIN                          GPIO_PIN_0 
#define BUZZER_GPIO_PORT                    GPIOB

#define  SI_PIN                             GPIO_PIN_6 
#define  SI_GPIO_PORT                       GPIOB

#define  DIGITAL_VALUE_PORT                  DIGITAL_DATA_GPIO_PORT->ODR

#define   SI_ON()       HAL_GPIO_WritePin(SI_GPIO_PORT, SI_PIN, GPIO_PIN_SET)     //开启可控硅
#define   SI_OFF()      HAL_GPIO_WritePin(SI_GPIO_PORT, SI_PIN, GPIO_PIN_RESET)  //关断可控硅

#define   DIG1_OFF     	HAL_GPIO_WritePin(DIGITAL_DIG_PORT, DIGITAL_DIG1_PIN, GPIO_PIN_RESET)   
#define   DIG2_OFF     	HAL_GPIO_WritePin(DIGITAL_DIG_PORT, DIGITAL_DIG2_PIN, GPIO_PIN_RESET)
#define   DIG1_ON      	HAL_GPIO_WritePin(DIGITAL_DIG_PORT, DIGITAL_DIG1_PIN, GPIO_PIN_SET)
#define   DIG2_ON     	HAL_GPIO_WritePin(DIGITAL_DIG_PORT, DIGITAL_DIG2_PIN, GPIO_PIN_SET)


//#define LEDx_GPIO_CLK_ENABLE(__INDEX__)    do {LED3_GPIO_CLK_ENABLE(); } while(0U)
//#define LEDx_GPIO_CLK_DISABLE(__INDEX__)   LED3_GPIO_CLK_DISABLE())

extern ADC_HandleTypeDef             AdcHandle;

extern void gpio_config(void);
extern u8 read_touch(void);
extern void buzzer_driver(u8 type);
extern void adc_enable(void);
#endif

