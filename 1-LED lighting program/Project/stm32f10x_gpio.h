#include "stm32f10x.h"

#define KEY1_GPIO_CLK ECC_APB2Periph_GPIOA
#define KEY1_GPIO_PORT GPIOA
#define KEY1_GPIO_PIN GPIO_Pin_0

#define KEY2_GPIO_CLK RCC_APB2Peripg_GPIOC
#define KEY2_GPIO_PORT GPIOC
#define KEY2_GPIO_PIN GPIO_Pin_13

#define LED_GPIO_CLK RCC_APB2Periph_GPIOB
#define LED_GPIO_PORT GPIOB
#define LEDG_GPIO_PIN GPIO_Pin_0
#define LEDB_GPIO_PIN GPIO_Pin_1
#define LEDR_GPIO_PIN GPIO_Pin_5

#define KEY_ON 1
#define KEY_OFF 0

uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON){
			while (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON){
			return KEY_ON;
			}	}	else 
			return KEY_OFF;

}
