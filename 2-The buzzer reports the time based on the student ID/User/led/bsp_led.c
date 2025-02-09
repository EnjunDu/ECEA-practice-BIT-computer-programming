#include "bsp_led.h"   

void LED_GPIO_Config(void)
{	
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd	(LED1_GPIO_CLK,ENABLE);
		/*Select the GPIO pin to be controlled*/		
		GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;	

		/*Set pin mode to push pull outputö*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*Set pin speed to 50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*Calling library functions to initialize GPIO*/
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	

		/*Turn off LED1 light*/
		GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
	
}
