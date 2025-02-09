#include "stm32f10x.h"

sbit FM = PA8;

void main()
{
	while (1){
	FM=1;//1.08us
	FM=0;
	}
}