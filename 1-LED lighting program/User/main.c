#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "bsp_led.h"

uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
    {
        while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)//scan whether KEY_ON has been pushed
        {
            return KEY_ON;
        }
    }
    else
    {
        return KEY_OFF;
    }
}

void Delay(__IO u32 nCount);

void LED_Color(uint8_t color)
{
    switch (color) {
        case 0:
            LED_RED;
            break;
        case 1:
            LED_GREEN;
            break;
        case 2:
            LED_BLUE;
            break;
        case 3:
            LED_WHITE;
            break;
    }
}

int main(void)
{
    LED_GPIO_Config();
	
    uint8_t color = -1;    // 0: Red, 1: Green, 2: Blue, 3: White
    uint8_t prev_color = -1;   // Store the previous color for KEY2 functionality

ff: while (1) {
        if (Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON) {
				
					//Detect KEY_ Is ON turned on to prevent KEY_ When ON is turned on, the light changes. Wait until the KEY1 key is pressed and bounces before changing the color
				while (Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON) {
            }
				
            prev_color = color;

            color = (color + 1) % 4;// use mod to simplize this project 

            LED_Color(color);
        }

        if (Key_Scan(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == KEY_ON) {
					 while (Key_Scan(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == KEY_ON) {
            }
            LED_RGBOFF;//Turn off all lights
						
						goto ff;//Enter the ff function and rerun
        }
    }
}
