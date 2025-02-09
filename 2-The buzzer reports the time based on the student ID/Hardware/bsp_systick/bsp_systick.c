#include "bsp_systick.h"

void SysTick_Delay_ms(__IO	uint32_t ms)
{
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000);

	for(i=0; i<ms; i++)
	{   
               while( !((SysTick->CTRL) & (1<<16)) ); 
        } 
              SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk; 
 }
