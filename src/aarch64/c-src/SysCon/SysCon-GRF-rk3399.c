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
            rcmd->From = 0x02U;
            rcmd->ShortResponse = 0x02U;
            rcmd->CauseSyndrome = 0xBBU;
            rcmd->Syndrome = 0x11U;
            break;
    }

    rcmd->From = 0x02U;
}

void syscon_grf_with_mask_conf_rk3399(uint64_t* cmd, uint64_t* conf, syscon_mode_e mode, unzero_rcmd_t* rcmd){
    uint8_t itteration = ((*cmd >> 32) & 0x3);
    UZRCMD_CHECKF_ITERATION(rcmd, 0x02U, 0x11U, 0U, 2U, itteration);
    
    for(int itteration = 0; itteration < ((*cmd >> 32) & 0x3); itteration++){
        uint8_t conf_bit = (*cmd >> ((4 * itteration) + 34)) & 0xF;

        uint16_t offset = (*cmd >> (16 * itteration)) & 0xFFFF;
        uint16_t mask = (*conf >> ((16 * itteration) + 32)) & 0xFFFF;
        uint16_t value = (*conf >> (16 * itteration)) & 0xFFFF;

        volatile uint32_t* GRF;
        switch(mode){
            case BASEGRF:
                UZRCMD_CHECKF_OFFSET(rcmd, 0x02U, 0xFFU, 0x0000U, 0xF7A0U, offset);
                GRF = (volatile uint32_t*)(0xFF770000 + offset);
                break;
            case PMUGRF:
                UZRCMD_CHECKF_OFFSET(rcmd, 0x02U, 0xFFU, 0x0000U, 0x30CU, offset);
                GRF = (volatile uint32_t*)(0xFF320000 + offset);
        }   

        *GRF = (value << conf_bit) | (mask << (conf_bit + 16));
    }
}

void syscon_grf_without_mask_conf_rk3399(uint64_t* cmd, uint64_t* conf, syscon_mode_e mode, unzero_rcmd_t* rcmd){
    uint8_t itteration = ((*cmd >> 32) & 0x3);
    UZRCMD_CHECKF_ITERATION(rcmd, 0x02U, 0x11U, 0U, 2U, itteration);
    
    for(int itteration = 0; itteration < ((*cmd >> 32) & 0x3); itteration++){
        uint8_t conf_bit = (*cmd >> ((6 * itteration) + 34)) & 0x3F;
        uint16_t offset = (*cmd >> (16 * itteration)) & 0xFFFF;
        uint32_t value = (*conf >> (32 * itteration)) & 0xFFFFFFFF;


        volatile uint32_t* GRF;
        switch(mode){
            case BASEGRF:
                UZRCMD_CHECKF_OFFSET(rcmd, 0x02U, 0xFFU, 0x0000U, 0xF7A0U, offset);
                GRF = (volatile uint32_t*)(0xFF770000 + offset);
                break;
            case PMUGRF:
                UZRCMD_CHECKF_OFFSET(rcmd, 0x02U, 0xFFU, 0x0000U, 0x30CU, offset);
                GRF = (volatile uint32_t*)(0xFF320000 + offset);
        }  

        *GRF = (value << conf_bit);
    }
}

alignas(8) syscon_hal_t Syscon_HAL = {
    .syscon_handle = &syscon_grf_handle_rk3399
};