#ifndef BSP_USART_H
#define BSP_USART_H

#include "stm32f10x.h"

void USART_Config(void);

void Usart_SendByte(USART_TypeDef * pUSARTx, uint8_t ch);

void Usart_SendString(USART_TypeDef * pUSARTx, char *str);

void Usart_SendStringDMA(USART_TypeDef *pUSARTx, const char *str);

#endif // BSP_USART_H
