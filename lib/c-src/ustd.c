#include<ustd.h>

void uprintf(uint8_t buffer[]){
    for(int index = 0; buffer[index] != 0x0;){
        if(UART_HAL.get_status() == 0){
            UART_HAL.send_char(buffer[index]);
            index++;
        }   
    }
}

void uprint8f(uint8_t src){
    char symbols[] = {"0123456789ABCDEF"};

    UART_HAL.send_char(symbols[src >> 4]);
    UART_HAL.send_char(symbols[src & 0xF]);
}

void uprint32f(uint32_t src){
    uprintf("0x");
    
    for(int index = 3; index >= 0; index--){
        uprint8f((src >> (index * 8)) & 0xFF);
    }

    uprintf("\r\n");
}

void uprint64f(uint64_t src){
    uprintf("0x");
    
    for(int index = 7; index >= 0; index--){
        uprint8f((src >> (index * 8)) & 0xFF);
    }

    uprintf("\r\n");
}