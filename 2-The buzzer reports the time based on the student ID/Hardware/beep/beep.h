#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"

//定义蜂鸣器端口、引脚和时钟，对应PA8
#define BEEP_PIN   GPIO_Pin_8
#define BEEP_PORT  GPIOA
#define BEEP_CLK   RCC_APB2Periph_GPIOA

//BEEP（ON/OFF）控制蜂鸣器开关
#define ON  1
#define OFF 0
#define BEEP(x) if (x) GPIO_SetBits(BEEP_PORT,BEEP_PIN);\
                else  GPIO_ResetBits( BEEP_PORT,BEEP_PIN);

//声明蜂鸣器初始化函数
void BEEP_Init(void);
#endif
