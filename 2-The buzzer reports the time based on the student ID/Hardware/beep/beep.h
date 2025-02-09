#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"

//����������˿ڡ����ź�ʱ�ӣ���ӦPA8
#define BEEP_PIN   GPIO_Pin_8
#define BEEP_PORT  GPIOA
#define BEEP_CLK   RCC_APB2Periph_GPIOA

//BEEP��ON/OFF�����Ʒ���������
#define ON  1
#define OFF 0
#define BEEP(x) if (x) GPIO_SetBits(BEEP_PORT,BEEP_PIN);\
                else  GPIO_ResetBits( BEEP_PORT,BEEP_PIN);

//������������ʼ������
void BEEP_Init(void);
#endif
