#ifndef  _USER_GPIO_H
#define  _USER_GPIO_H

#include  "global.h"
#include  "py32f0xx_hal.h"



#define DIGITAL_DATA_PIN                    GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9
#define DIGITAL_DATA_GPIO_PORT              GPIOA

#define DP_DATA_PIN                         GPIO_PIN_2
#define DP_DATA_GPIO_PORT                   GPIOF

#define DIGITAL_DIG1_PIN                    GPIO_PIN_0
#define DIGITAL_DIG2_PIN                    GPIO_PIN_1
#define DIGITAL_DIG3_PIN                    GPIO_PIN_0

#define DIGITAL_DIG1_PORT                   GPIOF
#define DIGITAL_DIG2_PORT                   GPIOF
#define DIGITAL_DIG3_PORT                   GPIOB

#define LED_RED                             GPIO_PIN_14
#define LED_GREEN                           GPIO_PIN_13
#define LED_GPIO_PORT                       GPIOA

#define  DIGITAL_VALUE_PORT                 DIGITAL_DATA_GPIO_PORT->ODR

#define   LED_RED_ON()       HAL_GPIO_WritePin(LED_GPIO_PORT, LED_RED, GPIO_PIN_SET)     //ºìµÆÁÁ
#define   LED_RED_OFF()      HAL_GPIO_WritePin(LED_GPIO_PORT, LED_RED, GPIO_PIN_RESET)  //ºìµÆÃð

#define   LED_GREEN_ON()       HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GREEN, GPIO_PIN_SET)     //ÂÌµÆÁÁ
#define   LED_GREEN_OFF()      HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GREEN, GPIO_PIN_RESET)  //ÂÌµÆÃð

#define   DIG1_ON     	HAL_GPIO_WritePin(DIGITAL_DIG1_PORT, DIGITAL_DIG1_PIN, GPIO_PIN_SET)   
#define   DIG2_ON     	HAL_GPIO_WritePin(DIGITAL_DIG2_PORT, DIGITAL_DIG2_PIN, GPIO_PIN_SET)
#define   DIG3_ON     	HAL_GPIO_WritePin(DIGITAL_DIG3_PORT, DIGITAL_DIG3_PIN, GPIO_PIN_SET)

#define   DIG1_OFF     	HAL_GPIO_WritePin(DIGITAL_DIG1_PORT, DIGITAL_DIG1_PIN, GPIO_PIN_RESET)   
#define   DIG2_OFF     	HAL_GPIO_WritePin(DIGITAL_DIG2_PORT, DIGITAL_DIG2_PIN, GPIO_PIN_RESET)
#define   DIG3_OFF     	HAL_GPIO_WritePin(DIGITAL_DIG3_PORT, DIGITAL_DIG3_PIN, GPIO_PIN_RESET)

#define   GPIO4_ON()      HAL_GPIO_WritePin(DIGITAL_DATA_GPIO_PORT, GPIO_PIN_6, GPIO_PIN_SET)
#define   GPIO5_ON()     	HAL_GPIO_WritePin(DIGITAL_DATA_GPIO_PORT, GPIO_PIN_7, GPIO_PIN_SET)
#define   GPIO6_ON()     	HAL_GPIO_WritePin(DIGITAL_DATA_GPIO_PORT, GPIO_PIN_9, GPIO_PIN_SET)
#define   DP_ON()         HAL_GPIO_WritePin(DP_DATA_GPIO_PORT, DP_DATA_PIN, GPIO_PIN_SET)

#define   GPIO4_OFF()     HAL_GPIO_WritePin(DIGITAL_DATA_GPIO_PORT, GPIO_PIN_6, GPIO_PIN_RESET)
#define   GPIO5_OFF()     HAL_GPIO_WritePin(DIGITAL_DATA_GPIO_PORT, GPIO_PIN_7, GPIO_PIN_RESET)
#define   GPIO6_OFF()     HAL_GPIO_WritePin(DIGITAL_DATA_GPIO_PORT, GPIO_PIN_9, GPIO_PIN_RESET)
#define   DP_OFF()        HAL_GPIO_WritePin(DP_DATA_GPIO_PORT,      DP_DATA_PIN, GPIO_PIN_RESET)




extern ADC_HandleTypeDef             AdcHandle;

extern void gpio_config(void);
extern u8 read_touch(void);
extern void buzzer_driver(u8 type);
extern void adc_enable(void);
#endif

