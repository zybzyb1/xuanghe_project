#ifndef  _USER_GPIO_H
#define  _USER_GPIO_H

#include  "global.h"



#define TOUCH_PIN                           GPIO_PIN_1
#define TOUCH_GPIO_PORT                     GPIOA
 
#define IR_PIN                              GPIO_PIN_2
#define IR_GPIO_PORT                        GPIOA

#define LIGHT_PIN                           GPIO_PIN_7
#define LIGHT_GPIO_PORT                     GPIOA


#define BUZZER_PIN                          GPIO_PIN_0 
#define BUZZER_GPIO_PORT                    GPIOF

#define  DELAY1_PIN                         GPIO_PIN_9 
#define  DELAY1_GPIO_PORT                   GPIOA
#define  DELAY2_PIN                         GPIO_PIN_1 
#define  DELAY2_GPIO_PORT                   GPIOB

#define  RED_PIN                            GPIO_PIN_6 
#define  RED_GPIO_PORT                      GPIOA
#define  GREEN_PIN                          GPIO_PIN_3 
#define  GREEN_GPIO_PORT                    GPIOA


#define   RED_ON()          HAL_GPIO_WritePin(RED_GPIO_PORT, RED_PIN, GPIO_PIN_RESET)     //开灯
#define   RED_OFF()         HAL_GPIO_WritePin(RED_GPIO_PORT, RED_PIN, GPIO_PIN_SET)       //关断 
#define   GREEN_ON()        HAL_GPIO_WritePin(GREEN_GPIO_PORT, GREEN_PIN, GPIO_PIN_RESET) //开启 
#define   GREEN_OFF()       HAL_GPIO_WritePin(GREEN_GPIO_PORT, GREEN_PIN, GPIO_PIN_SET)   //关断 

#define   DELAY1_OFF()     	HAL_GPIO_WritePin(DELAY1_GPIO_PORT, DELAY1_PIN, GPIO_PIN_RESET)   
#define   DELAY2_OFF()     	HAL_GPIO_WritePin(DELAY2_GPIO_PORT, DELAY2_PIN, GPIO_PIN_RESET)
#define   DELAY1_ON()      	HAL_GPIO_WritePin(DELAY1_GPIO_PORT, DELAY1_PIN, GPIO_PIN_SET)
#define   DELAY2_ON()     	HAL_GPIO_WritePin(DELAY2_GPIO_PORT, DELAY2_PIN, GPIO_PIN_SET)

#define   LIGHT_ON()        HAL_GPIO_WritePin(LIGHT_GPIO_PORT, LIGHT_PIN, GPIO_PIN_SET)     //开灯
#define   LIGHT_OFF()       HAL_GPIO_WritePin(LIGHT_GPIO_PORT, LIGHT_PIN, GPIO_PIN_RESET)   //关断 

//#define LEDx_GPIO_CLK_ENABLE(__INDEX__)    do {LED3_GPIO_CLK_ENABLE(); } while(0U)
//#define LEDx_GPIO_CLK_DISABLE(__INDEX__)   LED3_GPIO_CLK_DISABLE())
extern void gpio_config(void);
extern u8 read_touch(void);
extern void buzzer_driver(u8 type);
#endif

