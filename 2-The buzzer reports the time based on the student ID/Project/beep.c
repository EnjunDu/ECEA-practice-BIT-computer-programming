#include  "beep.h"
 
void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	GPIO_Init(GPIOF, &GPIO_InitStruct);
 
	GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}
