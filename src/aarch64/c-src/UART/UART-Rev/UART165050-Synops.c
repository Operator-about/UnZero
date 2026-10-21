#include"UART165050A.h"

uart_165050A_synops_t* UART165050A_Synops;

void uart165050A_init(uint8_t dlh, uint8_t dll){
    UART165050A_Synops->LCR = (1U << 7);
    UART165050A_Synops->TRD = dll;
    UART165050A_Synops->DEI = dlh;
    UART165050A_Synops->LCR = (0U << 7) | (3U << 0);
    UART165050A_Synops->FAR = (1U << 0);
    UART165050A_Synops->IFR = (1U << 0) | (1U << 1) | (1U << 2) | (2U << 4);
    UART165050A_Synops->FAR = (0U << 0); 
}

void uart165050A_send_char(char symbol){
    UART165050A_Synops->TRD = symbol;
}

uint8_t uart165050A_get_status(){
    return (UART165050A_Synops->USR & 0x1);
}

alignas(8) uart_hal_t UART_HAL = {
    .get_status = &uart165050A_get_status,
    .send_char = &uart165050A_send_char
};