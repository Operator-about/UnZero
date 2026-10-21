#include<ustd.h>

void uprintf(uint8_t buffer[]){
    for(int index = 0; buffer[index] != 0x0; index++){
        UART_HAL.send_char(buffer[index]);
    }
}