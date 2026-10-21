#pragma once

#include<type-UART.h>

extern uart_165050A_synops_t* UART165050A_Synops;

void uart165050A_init(uint8_t dlh, uint8_t dll);
void uart165050A_send_char(char symbol);
uint8_t uart165050A_get_status();
