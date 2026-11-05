#include<SysCon-GRF-rk3399.h>

void syscon_grf_handle_rk3399(uint64_t* cmd, uint64_t* conf, unzero_rcmd_t* rcmd){
    switch((*cmd >> 48) & 0xFF){
        case 1:
            syscon_grf_with_mask_conf_rk3399(cmd, conf, BASEGRF, rcmd);
            break;
        case 2:
            syscon_grf_without_mask_conf_rk3399(cmd, conf, BASEGRF, rcmd);
            break;
        case 3:
            syscon_grf_with_mask_conf_rk3399(cmd, conf, PMUGRF, rcmd);
            break;
        case 4:
            syscon_grf_without_mask_conf_rk3399(cmd, conf, PMUGRF, rcmd);
            break;
        default:
            break;
    }
}

void syscon_grf_with_mask_conf_rk3399(uint64_t* cmd, uint64_t* conf, syscon_mode_e mode, unzero_rcmd_t* rcmd){
    uint8_t itteration = ((*cmd >> 32) & 0x3);
    unzero_rcmd_itteration_check(rcmd, 2U, &itteration);
    UZRCMD_CHECKF(0x11U, 0x02U, rcmd);
    
    for(int itteration = 0; itteration < ((*cmd >> 32) & 0x3); itteration++){
        uint8_t conf_bit = (*cmd >> ((4 * itteration) + 34)) & 0xF;
        unzero_rcmd_bit_check(rcmd,  15U, &conf_bit);

        uint16_t offset = (*cmd >> (16 * itteration)) & 0xFFFF;
        uint16_t mask = (*conf >> ((16 * itteration) + 32)) & 0xFFFF;
        uint16_t value = (*conf >> (16 * itteration)) & 0xFFFF;

        UZRCMD_CHECKF(0xFFU, 0x02U, rcmd);

        volatile uint32_t* GRF;
        switch(mode){
            case BASEGRF:
                unzero_rcmd_offset_check(rcmd, 0xF7A0U, &offset);
                GRF = (volatile uint32_t*)(0xFF770000 + offset);
                break;
            case PMUGRF:
                unzero_rcmd_offset_check(rcmd, 0x30CU, &offset);
                GRF = (volatile uint32_t*)(0xFF320000 + offset);
        }   
        UZRCMD_CHECKF(0xFFU, 0x02U, rcmd);
        *GRF = (value << conf_bit) | (mask << (conf_bit + 16));
    }
}

void syscon_grf_without_mask_conf_rk3399(uint64_t* cmd, uint64_t* conf, syscon_mode_e mode, unzero_rcmd_t* rcmd){
    uint8_t itteration = ((*cmd >> 32) & 0x3);
    unzero_rcmd_itteration_check(rcmd, 2U, &itteration);
    UZRCMD_CHECKF(0x11U, 0x02U, rcmd);
    
    for(int itteration = 0; itteration < ((*cmd >> 32) & 0x3); itteration++){
        uint8_t conf_bit = (*cmd >> ((6 * itteration) + 34)) & 0x3F;
        unzero_rcmd_bit_check(rcmd, 31U, &conf_bit);

        uint16_t offset = (*cmd >> (16 * itteration)) & 0xFFFF;
        uint32_t value = (*conf >> (32 * itteration)) & 0xFFFFFFFF;

        UZRCMD_CHECKF(0xFFU, 0x02U, rcmd);

        volatile uint32_t* GRF;
        switch(mode){
            case BASEGRF:
                unzero_rcmd_offset_check(rcmd, 0xF7A0U, &offset);
                GRF = (volatile uint32_t*)(0xFF770000 + offset);
                break;
            case PMUGRF:
                unzero_rcmd_offset_check(rcmd, 0x30CU, &offset);
                GRF = (volatile uint32_t*)(0xFF320000 + offset);
        }    
        UZRCMD_CHECKF(0xFFU, 0x02U, rcmd);
        *GRF = (value << conf_bit);
    }
}

alignas(8) syscon_hal_t Syscon_HAL = {
    .syscon_handle = &syscon_grf_handle_rk3399
};