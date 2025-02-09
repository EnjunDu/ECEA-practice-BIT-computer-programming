#include "beep.h"


void BEEP_Init(void)
{
    //实例化配置GPIO模式和速度结构体
    GPIO_InitTypeDef GPIO_InitStruct;
    
    //使能蜂鸣器时钟
    RCC_APB2PeriphClockCmd(BEEP_CLK, ENABLE );
    
    //配置端口输出并初始化
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = BEEP_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;      
    GPIO_Init( BEEP_PORT, &GPIO_InitStruct);
    
    //蜂鸣器初始化后不响
    BEEP(0);
}
