#ifndef LED_PWM_H
#define LED_PWM_H

#include "stm32f10x.h"

#define COLOR_TIM_GPIO_CLK   RCC_APB2Periph_GPIOB

#define COLOR_RED_TIM_LED_PIN      GPIO_Pin_5  
#define COLOR_GREEN_TIM_LED_PIN    GPIO_Pin_0  
#define COLOR_BLUE_TIM_LED_PIN     GPIO_Pin_1

#define COLOR_RED_TIM_LED_PORT     GPIOB
#define COLOR_GREEN_TIM_LED_PORT   GPIOB
#define COLOR_BLUE_TIM_LED_PORT    GPIOB

#define COLOR_TIM_CLK             RCC_APB1Periph_TIM3
#define COLOR_TIMx                TIM3

#define COLOR_TIM4_CLK             RCC_APB1Periph_TIM4
#define COLOR_TIMx4                TIM4
void COLOR_TIMx_GPIO_Config(void);

void COLOR_PWM_Config(void);

void COLOR_TIMx4_Config(void);

void TIM1_IRQHandler(void);

#endif
