#include "LED_PWM.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h" 
#include "stm32f10x_tim.h" 

void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}
void COLOR_TIMx_GPIO_Config(void)
	{
	RCC_Configuration();
		
	RCC_APB2PeriphClockCmd(COLOR_TIM_GPIO_CLK, ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
    
    // red
    GPIO_InitStructure.GPIO_Pin = COLOR_RED_TIM_LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(COLOR_RED_TIM_LED_PORT, &GPIO_InitStructure);

    // green
    GPIO_InitStructure.GPIO_Pin = COLOR_GREEN_TIM_LED_PIN;
    GPIO_Init(COLOR_GREEN_TIM_LED_PORT, &GPIO_InitStructure);

    // blue
    GPIO_InitStructure.GPIO_Pin = COLOR_BLUE_TIM_LED_PIN;
    GPIO_Init(COLOR_BLUE_TIM_LED_PORT, &GPIO_InitStructure);
}

void COLOR_PWM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(COLOR_TIM_CLK,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 255;
	TIM_TimeBaseStructure.TIM_Prescaler = 4000;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(COLOR_TIMx,&TIM_TimeBaseStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStucture;
	TIM_OCInitStucture.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStucture.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStucture.TIM_Pulse = 0;
	TIM_OCInitStucture.TIM_OCPolarity = TIM_OCPolarity_Low;
	
    //  OC2 red
    TIM_OC2Init(COLOR_TIMx, &TIM_OCInitStucture);
    TIM_OC2PreloadConfig(COLOR_TIMx, TIM_OCPreload_Enable);

    //  OC3 green
    TIM_OC3Init(COLOR_TIMx, &TIM_OCInitStucture);
    TIM_OC3PreloadConfig(COLOR_TIMx, TIM_OCPreload_Enable);

    //  OC4 blue
    TIM_OC4Init(COLOR_TIMx, &TIM_OCInitStucture);
    TIM_OC4PreloadConfig(COLOR_TIMx, TIM_OCPreload_Enable);

	
	TIM_ARRPreloadConfig(COLOR_TIMx,ENABLE);
	TIM_Cmd(COLOR_TIMx,ENABLE);
	
}

void COLOR_TIMx4_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(COLOR_TIM4_CLK, ENABLE);
/*Clock Frequency: Assuming the system clock frequency is 72 MHz.
	Prescaler Value: The prescaler is set to 10000 - 1.
	Period Value: The period is set to 7200 - 1.
	Consequently, the timer clock frequency after prescaling is 7.2 kHz (72 MHz / 10000).
	The timer starts counting from 0 and triggers an interrupt when it reaches a count of 7199 (7200 - 1). 
	The time interval can be calculated as follows:
	Time = Number of Periods / Timer Clock Frequency
	Time = 7199 / 7200 ˜ 0.999722 seconds
	Therefore, in practice, the timer will trigger an interrupt after approximately 0.999722 
	seconds, which is close to 1 second.*/
    TIM_TimeBaseStructure.TIM_Period = 7200 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler =10000 - 1; 
	
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(COLOR_TIMx4, &TIM_TimeBaseStructure);

    TIM_ITConfig(COLOR_TIMx4, TIM_IT_Update, ENABLE); // Enable update interrupt
    TIM_Cmd(COLOR_TIMx4, ENABLE);
}

// Add these definitions at the beginning of your .c file
typedef enum {
    COLOR_RED,
    COLOR_ORANGE,
    COLOR_YELLOW,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_BLUE,
    COLOR_PURPLE
} ColorState;

int currentColor=-1;

void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(COLOR_TIMx4, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(COLOR_TIMx4, TIM_IT_Update);

        // Update the current color state
        currentColor = (currentColor + 1) % 7; // Cycle through 0 to 6

        // Update the PWM values based on the current color state
switch (currentColor) {
	
    case COLOR_RED:
        COLOR_TIMx->CCR2 = 255;
				COLOR_TIMx->CCR3 = 0;
				COLOR_TIMx->CCR4 = 0;
        break;
    case COLOR_ORANGE:
        COLOR_TIMx->CCR2 = 255;
				/*In fact, when the value of CCR3 is set to 128, it represents the standard RGB orange color parameter. 
					However, after visual confirmation, setting it to 97 gives a color that more closely resembles orange. 
					Therefore, I chose to set it to 97.*/
				COLOR_TIMx->CCR3 = 97	;
				COLOR_TIMx->CCR4 = 0;
        break;
    case COLOR_YELLOW:
        COLOR_TIMx->CCR2 = 255;
				COLOR_TIMx->CCR3 = 255;
				COLOR_TIMx->CCR4 = 0;
        break;
    case COLOR_GREEN:
				COLOR_TIMx->CCR2 = 0;
				COLOR_TIMx->CCR3 = 255;
				COLOR_TIMx->CCR4 = 0;
        break;
    case COLOR_CYAN:
        COLOR_TIMx->CCR2 = 0;
				COLOR_TIMx->CCR3 = 255;
				COLOR_TIMx->CCR4 = 255;
        break;
    case COLOR_BLUE:
        COLOR_TIMx->CCR2 = 0;
				COLOR_TIMx->CCR3 = 0;
				COLOR_TIMx->CCR4 = 255;
        break;
    case COLOR_PURPLE:
        COLOR_TIMx->CCR2 = 128;
				COLOR_TIMx->CCR3 = 0;
				COLOR_TIMx->CCR4 = 255;
        break;
}
    }
}
