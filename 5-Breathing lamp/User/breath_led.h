#ifndef BREATH_LED_H
#define BREATH_LED_H

#include "stm32f10x.h"

#define COLOR_TIM_GPIO_CLK   RCC_APB2Periph_GPIOB

#define COLOR_RED_TIM_LED_PIN      GPIO_Pin_5  
#define COLOR_GREEN_TIM_LED_PIN    GPIO_Pin_0  
#define COLOR_BLUE_TIM_LED_PIN     GPIO_Pin_1

#define COLOR_RED_TIM_LED_PORT     GPIOB
#define COLOR_GREEN_TIM_LED_PORT   GPIOB
#define COLOR_BLUE_TIM_LED_PORT    GPIOB

#define COLOR_TIM_CLK             RCC_APB1Periph_TIM3
#define COLOR_TIM                TIM3

#define BASIC_TIM                TIM6
#define BASIC_TIM_CLK            RCC_APB1Periph_TIM6
	
	void COLOR_TIMx_GPIO_Config(void);
	
	void COLOR_TIMx_Mode_Config(void);
	
	void BASIC_TIM_Init(void);
	
	void BASIC_TIM_NVIC_Config(void);

#endif
