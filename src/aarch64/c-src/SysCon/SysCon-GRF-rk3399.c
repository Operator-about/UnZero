#include<SysCon-GRF-rk3399.h>
#include<ustd.h>

void syscon_grf_conf_rk3399(uint64_t* cmd, uint64_t* conf){
    for(int itteration = 0; itteration < ((*cmd >> 32) & 0x3); itteration++){
        uint8_t conf_bit = (*cmd >> ((4 * itteration) + 34)) & 0xF;
        uint16_t offset = (*cmd >> (16 * itteration)) & 0xFFFF;
        uint16_t mask = (*conf >> ((16 * itteration) + 32)) & 0xFFFF;
        uint16_t value = (*conf >> (16 * itteration)) & 0xFFFF;

        volatile uint32_t* GRF = (volatile uint32_t*)(0xFF770000 + offset);
        *GRF = (value << conf_bit) | (mask << (conf_bit + 16));
    }
}