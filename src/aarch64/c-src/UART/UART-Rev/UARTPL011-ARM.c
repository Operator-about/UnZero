#include<UARTPL011.h>

uart_pl011_arm_t* UARTPL011_ARM;

void uartpl011_init(uint16_t ibrd, uint8_t fbrd){
    UARTPL011_ARM->CR = (0U << 0);
    UARTPL011_ARM->IBRD = ibrd;
    UARTPL011_ARM->FBRD = (fbrd & 0x3F);
    UARTPL011_ARM->LCR_H = (1U << 4) | (3U << 5);  
    UARTPL011_ARM->IFLS = (1U << 0);
    UARTPL011_ARM->CR = (1U << 8) | (1U << 0);
}

void uartpl011_send_char(char symbol){
    UARTPL011_ARM->DR = symbol;
}

uint8_t uartpl011_get_status(){
    return (UARTPL011_ARM->FR >> 3) & 0x1;
}

alignas(8) uart_hal_t UART_HAL = {
    .get_status = &uartpl011_get_status,
    .send_char = &uartpl011_send_char
};