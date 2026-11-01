#include<SysCon-GRF-rk3399.h>

void syscon_grf_handle_rk3399(uint64_t* cmd, uint64_t* conf){
    switch((*cmd >> 48) & 0xFF){
        case 1:
            syscon_grf_with_mask_conf_rk3399(cmd, conf, BASEGRF);
            break;
        case 2:
            syscon_grf_without_mask_conf_rk3399(cmd, conf, BASEGRF);
            break;
        case 3:
            syscon_grf_with_mask_conf_rk3399(cmd, conf, PMUGRF);
            break;
        case 4:
            syscon_grf_without_mask_conf_rk3399(cmd, conf, PMUGRF);
            break;
        default:
            break;
    }
}

void syscon_grf_with_mask_conf_rk3399(uint64_t* cmd, uint64_t* conf, syscon_mode_e mode){
    for(int itteration = 0; itteration < ((*cmd >> 32) & 0x3); itteration++){
        uint8_t conf_bit = (*cmd >> ((4 * itteration) + 34)) & 0xF;
        uint16_t offset = (*cmd >> (16 * itteration)) & 0xFFFF;
        uint16_t mask = (*conf >> ((16 * itteration) + 32)) & 0xFFFF;
        uint16_t value = (*conf >> (16 * itteration)) & 0xFFFF;

        volatile uint32_t* GRF;
        switch(mode){
            case BASEGRF:
                GRF = (volatile uint32_t*)(0xFF770000 + offset);
                break;
            case PMUGRF:
                GRF = (volatile uint32_t*)(0xFF320000 + offset);
        }   
        *GRF = (value << conf_bit) | (mask << (conf_bit + 16));
    }
}

void syscon_grf_without_mask_conf_rk3399(uint64_t* cmd, uint64_t* conf, syscon_mode_e mode){
    for(int itteration = 0; itteration < ((*cmd >> 32) & 0x3); itteration++){
        uint8_t conf_bit = (*cmd >> ((6 * itteration) + 34)) & 0x3F;
        uint16_t offset = (*cmd >> (16 * itteration)) & 0xFFFF;
        uint16_t value = (*conf >> (32 * itteration)) & 0xFFFFFFFF;

        volatile uint32_t* GRF;
        switch(mode){
            case BASEGRF:
                GRF = (volatile uint32_t*)(0xFF770000 + offset);
                break;
            case PMUGRF:
                GRF = (volatile uint32_t*)(0xFF320000 + offset);
        }   
        *GRF = (value << conf_bit);
    }
}

alignas(8) syscon_hal_t Syscon_HAL = {
    .syscon_handle = &syscon_grf_handle_rk3399
};