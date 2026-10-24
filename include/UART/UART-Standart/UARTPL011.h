#pragma once

#include<type-UART.h>
#include<stdalign.h>

extern uart_pl011_arm_t* UARTPL011_ARM;

void uartpl011_init(uint16_t ibrd, uint8_t fbrd);
void uartpl011_send_char(char symbol);
uint8_t uartpl011_get_status();