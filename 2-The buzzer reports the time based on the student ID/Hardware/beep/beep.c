#include "beep.h"


void BEEP_Init(void)
{
    //ʵ��������GPIOģʽ���ٶȽṹ��
    GPIO_InitTypeDef GPIO_InitStruct;
    
    //ʹ�ܷ�����ʱ��
    RCC_APB2PeriphClockCmd(BEEP_CLK, ENABLE );
    
    //���ö˿��������ʼ��
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = BEEP_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;      
    GPIO_Init( BEEP_PORT, &GPIO_InitStruct);
    
    //��������ʼ������
    BEEP(0);
}
