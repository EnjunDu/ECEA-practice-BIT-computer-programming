#include "stm32f10x.h"
#include "breath_led.h"
#include "stm32f10x_gpio.h" 
#include "stm32f10x_tim.h" 


void COLOR_TIMx_GPIO_Config(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO,ENABLE);
	
	RCC_APB2PeriphClockCmd(COLOR_TIM_GPIO_CLK, ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	//red
	GPIO_InitStructure.GPIO_Pin = COLOR_RED_TIM_LED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(COLOR_RED_TIM_LED_PORT,&GPIO_InitStructure);
	
	//green
	GPIO_InitStructure.GPIO_Pin = COLOR_GREEN_TIM_LED_PIN;
	GPIO_Init(COLOR_GREEN_TIM_LED_PORT,&GPIO_InitStructure);
	
	//blue
	GPIO_InitStructure.GPIO_Pin = COLOR_BLUE_TIM_LED_PIN;
	GPIO_Init(COLOR_BLUE_TIM_LED_PORT,&GPIO_InitStructure);
}

void COLOR_TIMx_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(COLOR_TIM_CLK,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 255;
	TIM_TimeBaseStructure.TIM_Prescaler = 7;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(COLOR_TIM,&TIM_TimeBaseStructure);
	
	TIM_ARRPreloadConfig(COLOR_TIM,ENABLE);
	
	TIM_Cmd(COLOR_TIM,ENABLE);
	
	TIM_OCInitTypeDef		TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	
	
    //  OC2 red
    TIM_OC2Init(COLOR_TIM, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable);

    //  OC3 green
    TIM_OC3Init(COLOR_TIM, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable);

    //  OC4 blue
    TIM_OC4Init(COLOR_TIM, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable);

}

void BASIC_TIM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(BASIC_TIM_CLK,ENABLE);
	
//Since the last digit of my student ID is 5, the breathing LED blink period should be 1.5 seconds. The calculation is as follows:
	
/*Target duration = 1.5 seconds = 1500 milliseconds
Timer clock frequency = 72 MHz = 72,000,000 Hz
Counting frequency per second = 10 times
Counting times = 10 times/second * 1.5 seconds = 15 times
Prescaler = (Timer clock frequency * Target duration) / Counting times - 1
Period = Counting times - 1
According to the calculations above, the prescaler is approximately 4800000, and the period is 14.*/
	
	TIM_TimeBaseStructure.TIM_Prescaler = 4800000;
	TIM_TimeBaseStructure.TIM_Period = 14;
	TIM_TimeBaseInit(BASIC_TIM,&TIM_TimeBaseStructure);
	
	TIM_ARRPreloadConfig(BASIC_TIM,ENABLE);
	TIM_Cmd(BASIC_TIM,ENABLE);
	
	TIM_ClearFlag(BASIC_TIM,TIM_FLAG_Update);
	TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
}

void BASIC_TIM_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
// ColorState enumeration to represent different colors

typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_WHITE
} ColorState;

uint16_t breathCounter = 0;

uint8_t breathDirection = 1; 

int currentColor=0;
						
void TIM6_IRQHandler(void)
{
    if (TIM_GetITStatus(BASIC_TIM, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(BASIC_TIM, TIM_IT_Update);
        
        // Update the PWM duty cycle (CCR values) based on the currentColor
        switch (currentColor) {
            case COLOR_RED:
                TIM_SetCompare2(COLOR_TIM, breathCounter); // Red
                TIM_SetCompare3(COLOR_TIM, 0);
                TIM_SetCompare4(COLOR_TIM, 0);
                break;
            case COLOR_GREEN:
                TIM_SetCompare2(COLOR_TIM, 0);
                TIM_SetCompare3(COLOR_TIM, breathCounter); // Green
                TIM_SetCompare4(COLOR_TIM, 0);
                break;
            case COLOR_BLUE:
                TIM_SetCompare2(COLOR_TIM, 0);
                TIM_SetCompare3(COLOR_TIM, 0);
                TIM_SetCompare4(COLOR_TIM, breathCounter); // Blue
                break;
            case COLOR_WHITE:
                TIM_SetCompare2(COLOR_TIM, breathCounter); // Red
                TIM_SetCompare3(COLOR_TIM, breathCounter); // Green
                TIM_SetCompare4(COLOR_TIM, breathCounter); // Blue
                break;
            default:
                break;
        }

        // Update the breathCounter and direction
				//Implementing a specific function to achieve a breathing effect for the LED.
        if (breathDirection) {
            breathCounter++;
            if (breathCounter >= 255) {
                breathCounter = 255;
                breathDirection = 0;
            }
        } else {
            breathCounter--;
            if (breathCounter == 0) {
                breathCounter = 0;
                breathDirection = 1;
                currentColor = (currentColor + 1) % 4;
            }
        }
    }
}
