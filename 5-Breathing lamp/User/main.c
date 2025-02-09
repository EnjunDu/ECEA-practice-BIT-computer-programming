#include "stm32f10x.h"
#include "breath_led.h"
#include "stm32f10x_gpio.h" 
#include "stm32f10x_tim.h" 

int main(void)
{

	 COLOR_TIMx_GPIO_Config();
	
	 COLOR_TIMx_Mode_Config();
	
	 BASIC_TIM_Init();
	
	 BASIC_TIM_NVIC_Config();
	
		TIM_Cmd(BASIC_TIM, ENABLE);

	while (1) {
       
        }
 }
