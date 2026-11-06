#include<Clk-CRU-rk3399.h>

clk_pmucru_rk3399_t* PMU_CRU;
clk_cru_rk3399_t* CRU;
clk_cru_mode_rk3399_t Mode;

void clk_cru_handle_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info, unzero_rcmd_t* rcmd){
    switch((*cmd >> 55) & 0x1){
        case 1:
            Mode = PMUCRU;
            break;
        case 0:
            Mode = BASECRU;
            break;
        default:
            Mode = BASECRU;
            break;
    }

    switch((*cmd >> 48) & 0x7F){
        case 3:
            clk_cru_conf_gate_rk3399(cmd, field_info, reg_info, rcmd);
            break;
        case 4:
            clk_cru_conf_reset_rk3399(cmd, field_info, reg_info, rcmd);
            break;
        case 2: //10-bit Div's
            clk_cru_conf_sel_rk3399(cmd, field_info, reg_info, mask_info, 12U, rcmd);
            break;
        case 1: //8-bit Div's
            clk_cru_conf_sel_rk3399(cmd, field_info, reg_info, mask_info, 8U, rcmd);
            break;
        default:
            rcmd->From = 0x01U;
            rcmd->ShortResponse = 0x02U;
            rcmd->CauseSyndrome = 0xBBU;
            rcmd->Syndrome = 0x11U;
            break;
    }

    rcmd->From = 0x01U;
}

void clk_cru_pll_handle_rk3399(uint64_t* cmd, unzero_rcmd_t* rcmd){
    clk_cru_pll_seq_mode_rk3399_e mode = FULL;
    switch((*cmd >> 48) & 0xFF){
        case 0:
            mode = FULL;
            break;
        case 1:
            mode = SHUTDOWN_ONLY;
            break;
        default:
            rcmd->From = 0x01U;
            rcmd->ShortResponse = 0x02U;
            rcmd->CauseSyndrome = 0xBBU;
            rcmd->Syndrome = 0x11U;
            break;
    }
    
    clk_cru_pll_conf_rk3399(cmd, mode, rcmd);
    rcmd->From = 0x01U;
}

void clk_cru_conf_sel_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info, uint8_t div_mull, unzero_rcmd_t* rcmd){
    uint8_t itteration = ((*reg_info >> 32) & 0xFF);
    UZRCMD_CHECKF_ITERATION(rcmd, 0x01U, 0x11U, 0U, 4U, itteration);

    for(int index = 0; index < itteration; index++){
        uint16_t current_div;
        switch(div_mull){
            case 8:
                current_div = (*cmd >> (index * div_mull)) & 0xFF;
                break;
            case 12:
                current_div = (*cmd >> (index * div_mull)) & 0xFFF;
                break;
        }
        UZRCMD_CHECKF_VALUE(rcmd, 0x01U, 0xFFU, 1024U, 250U, current_div);

        uint8_t current_pll = (*cmd >> ((index * 3) + 32)) & 0x7; 

        uint8_t current_div_bit = (*field_info >> (index * 4)) & 0xF;
        uint8_t current_pll_bit = (*field_info >> ((index * 4) + 16)) & 0xF;

        uint16_t mask_div = (*mask_info >> (index * 12)) & 0xFFF;
        uint8_t mask_pll = (*mask_info >> ((index * 3) + 48)) & 0x7;

        switch(Mode){
            case BASECRU:
                CRU->CLKSEL_CON[((*reg_info >> (8 * index)) & 0xFF)] = (current_div << current_div_bit) | (current_pll << current_pll_bit) | (mask_div << (current_div_bit + 16)) | (mask_pll << (current_pll_bit + 16));
                break;
            case PMUCRU:
                PMU_CRU->CLKSEL_CON[((*reg_info >> (8 * index)) & 0xFF)] = (current_div << current_div_bit) | (current_pll << current_pll_bit) | (mask_div << (current_div_bit + 16)) | (mask_pll << (current_pll_bit + 16));
        }
    }
}

void clk_cru_conf_gate_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, unzero_rcmd_t* rcmd){
    uint8_t itteration = ((*reg_info >> 32) & 0xFF);
    UZRCMD_CHECKF_ITERATION(rcmd, 0x01U, 0x11U, 0U, 4U, itteration);
    
    for(int index = 0; index < itteration; index++){
        uint16_t current_gate = (*cmd >> (8 * index)) & 0xFF;
        uint8_t current_gate_bit = (*field_info >> (4 * index)) & 0xF;
        uint16_t mask_gate = (*field_info >> ((8 * index) + 16) & 0xFF);

        
        switch(Mode){
            case BASECRU:
                CRU->CLKGATE_CON[((*reg_info >> (8 * index)) & 0xFF)] = (current_gate << current_gate_bit) | (mask_gate << (current_gate_bit + 16));
                break;
            case PMUCRU:
                PMU_CRU->CLKGATE_CON[((*reg_info >> (8 * index)) & 0xFF)] = (current_gate << current_gate_bit) | (mask_gate << (current_gate_bit + 16));
                break;
        }
    }
}

void clk_cru_conf_reset_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, unzero_rcmd_t* rcmd){
    uint8_t itteration = ((*reg_info >> 32) & 0xFF);
    UZRCMD_CHECKF_ITERATION(rcmd, 0x01U, 0x11U, 0U, 4U, itteration);
    
    for(int index = 0; index < ((*reg_info >> 32) & 0xFF); index++){
        uint16_t current_reset = (*cmd >> (8 * index)) & 0xFF;
        uint8_t current_reset_bit = (*field_info >> (4 * index)) & 0xF;
        uint16_t mask_reset = (*field_info >> ((8 * index) + 16) & 0xFF);
        
        switch(Mode){
            case BASECRU:
                CRU->CLKRESET_CON[((*reg_info >> (8 * index)) & 0xFF)] = (current_reset << current_reset_bit) | (mask_reset << (current_reset_bit + 16));
                break;
            case PMUCRU:
                PMU_CRU->CLKRESET_CON[((*reg_info >> (8 * index)) & 0xFF)] = (current_reset << current_reset_bit) | (mask_reset << (current_reset_bit + 16));
        }
    }
}

void clk_cru_pll_conf_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode, unzero_rcmd_t* rcmd){
    uint16_t feedback = (*cmd & 0x7FF);
    uint16_t offset = ((*cmd >> 12) & 0xFF);
    uint8_t ref_div = (*cmd >> 28) & 0x3F;
    uint8_t post_div1 = (*cmd >> 34) & 0x7;
    uint8_t post_div2 = (*cmd >> 37) & 0x7;
    clk_cru_pll_pattern_t* pll = (clk_cru_pll_pattern_t*)(0xFF760000 + ((*cmd >> 12) & 0xFF));

    UZRCMD_CHECKF_VALUE(rcmd, 0x01U, 0xFFU, 3201U, 3100U, feedback);
    UZRCMD_CHECKF_VALUE(rcmd, 0x01U, 0xFFU, 64U, 60U, ref_div);
    UZRCMD_CHECKF_VALUE(rcmd, 0x01U, 0xFFU, 8U, 6U, post_div1);
    UZRCMD_CHECKF_VALUE(rcmd, 0x01U, 0xFFU, 8U, 6U, post_div2);
    UZRCMD_CHECKF_OFFSET(rcmd, 0x01U, 0xFFU, 0x0000U, 0x00D4U, offset);
    offset = 0x0;

    
    switch(mode){
        case FULL:
            pll->PLL0 = (feedback << 0) | (0x7FFU << 16);
            pll->PLL1 = (ref_div << 0) | (post_div1 << 8) | (post_div2 << 12) | (0x3F << 16) | (0x7 << 24) | (0x7 << 28);
            pll->PLL3 = (0U << 0) | (1U << 8) | (0x1U << 16) | (0x3U << 24);

            while((pll->PLL2 & (1U << 31)) == 0){
                __asm__("NOP");
            }
            break;
        case SHUTDOWN_ONLY:
            pll->PLL3 = (1U << 0) | (0x1U << 16);
            break;
    }
}

alignas(8) clk_hal_t CLK_HAL = {
    .clk_handle = &clk_cru_handle_rk3399,
    .clk_pll_handle = &clk_cru_pll_handle_rk3399
};