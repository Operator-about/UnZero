#pragma once

#include<stdint.h>
#include<stdalign.h>

typedef struct{
    volatile uint32_t TRD;
    volatile uint32_t DEI;
    volatile uint32_t IFR;
    volatile uint32_t LCR;
    uint32_t RESERVE_1[1];
    volatile uint32_t LSR;
    uint32_t RESERVE_2[22];
    volatile uint32_t FAR;
    uint32_t RESERVE_3[2];
    volatile uint32_t USR;
}uart_165050A_synops_t;

typedef enum{
    DISABLE,
    ENABLE
}uart_irq_mode_e;

typedef struct{
    void (*send_char)(char symbol);
    void (*irq_de)(uart_irq_mode_e mode);
    uint8_t (*get_status)();
}uart_hal_t;

extern alignas(8) uart_hal_t UART_HAL;