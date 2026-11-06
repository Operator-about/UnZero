#pragma once

#include<stdint.h>
#include<UART165050A.h>

void uprintf(uint8_t buffer[]);
void uprint8f(uint8_t src);
void uprint32f(uint32_t src);
void uprint64f(uint64_t src);