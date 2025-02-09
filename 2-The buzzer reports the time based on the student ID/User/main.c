#include "stm32f10x.h"
#include "bsp_led.h"
#include "beep.h"
#include "bsp_systick.h"

int main()
{
		LED_GPIO_Config();	
    BEEP_Init();
		
	int i=0;
    while(i<1)	/*My student number is 112022xxx5,which means  n=mod(5,5)+1=1*/
    {
        BEEP(1);
				LED1_ON;//light the red light
    SysTick_Delay_ms(250);
        BEEP(0);
				LED1_OFF;// turn off the red light
			SysTick_Delay_ms(1000);			
				i++;
    }
			BEEP(1);
			LED1_ON;
			SysTick_Delay_ms(1000);
			BEEP(0); 
			LED1_OFF;
}
