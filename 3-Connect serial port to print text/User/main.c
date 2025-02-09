#include "stm32f10x.h"
#include "bsp_usart.h"

// define the starting address of the Flash's storing room
#define FLASH_STRING_ADDRESS 0x08008000

// Define the string which will be stored in FLASH
const char flashString[] = "And you are beautiful too!(sending from FLASH!)\r\n";

int main(void) {
    USART_Config();//initialization
		Usart_SendString(USART1,"dgg is so handsome,isn't he?");
 // Store the string in FLASH
    FLASH_Unlock();//unlock the FLASH
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    uint32_t flashAddress = FLASH_STRING_ADDRESS;
    const char *sourceAddress = flashString;
    while (*sourceAddress) {
        FLASH_ProgramWord(flashAddress, *sourceAddress);
        flashAddress += 4; // Increment by 4 bytes for each word
        sourceAddress++;
    }
    FLASH_Lock();//Lock the FLASH

    // Transmit the stored string using DMA
    Usart_SendStringDMA(USART1, flashString);

    while (1) {
    }
}
