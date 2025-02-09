#include "stm32f10x.h"
#include "LED_PWM.h"

int main(void)
{
		//Ensure interrupt priority
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	
    COLOR_TIMx_GPIO_Config();
    COLOR_PWM_Config();
    COLOR_TIMx4_Config();
			while (1) {   
    }
}
