#include "bsp_usart.h"
#include "stm32f10x.h"

void USART_Config(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
	
  //USART1 Tx(PA.09) 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //USART1 Rx(PA.10) 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  USART_InitTypeDef USART_InitStructure;
  //USART1
  USART_InitStructure.USART_BaudRate = 9600; 
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
  USART_InitStructure.USART_StopBits = USART_StopBits_2; 
  USART_InitStructure.USART_Parity = USART_Parity_No; 
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
  USART_Init(USART1, &USART_InitStructure);
	
  USART_Cmd(USART1, ENABLE);  
}
void Usart_SendByte(USART_TypeDef * pUSARTx, uint8_t ch)
{
  USART_SendData(pUSARTx, ch);  
  while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);  
}

void Usart_SendString(USART_TypeDef * pUSARTx, char *str)
{
  unsigned int k=0;
  do 
  {
    Usart_SendByte(pUSARTx, *(str + k));
    k++;
  }while(*(str + k) != '\0'); 

  while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET) 
  {}
}
void Usart_SendStringDMA(USART_TypeDef *pUSARTx, const char *str)
{
    DMA_InitTypeDef DMA_InitStructure;
    // Configure DMA
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA1_Channel4); // USART1 TX channel

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&pUSARTx->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)str;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; // Transfer from FLASH to PC
    DMA_InitStructure.DMA_BufferSize = strlen(str);//Define using bytes of a string
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//Data will be transmitted in bytes from the source address to the destination address
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; // Memory to memory disabled
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);

    USART_DMACmd(pUSARTx, USART_DMAReq_Tx, ENABLE);    // Open USART DMA TX

    DMA_Cmd(DMA1_Channel4, ENABLE);    // Enable DMA channel

}
