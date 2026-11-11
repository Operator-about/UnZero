#include<Clk-CRU-rk3399.h>
#include<ustd.h>

clk_cru_mode_rk3399_t Mode;

void clk_cru_handle_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info, unzero_rcmd_t* rcmd){
    switch((*cmd >> 48) & 0xFF){
        case 14:
            Mode = PMUCRU;
            clk_cru_conf_other_register(cmd, field_info, reg_info, rcmd);
            break;
        case 13:
            Mode = BASECRU;
            clk_cru_conf_other_register(cmd, field_info, reg_info, rcmd);
            break;
        case 5 ... 6:
            Mode = PMUCRU;
            clk_cru_conf_gate_reset_rk3399(cmd, field_info, reg_info, rcmd);
            break;
        case 4:
            Mode = PMUCRU;
            clk_cru_conf_sel_rk3399(cmd, field_info, reg_info, mask_info, rcmd);
            break;
        case 2 ... 3:
            Mode = BASECRU;
            clk_cru_conf_gate_reset_rk3399(cmd, field_info, reg_info, rcmd);
            break;
        case 1:
            Mode = BASECRU;
            clk_cru_conf_sel_rk3399(cmd, field_info, reg_info, mask_info, rcmd);
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
    clk_cru_pll_seq_mode_rk3399_e mode_pll_protocol = FULL;
    switch((*cmd >> 48) & 0xFF){
        case 1:
            mode_pll_protocol = FULL;
            Mode = BASECRU;
            break;
        case 2:
            mode_pll_protocol = SHUTDOWN_ONLY;
            Mode = BASECRU;
            break;
        case 3:
            mode_pll_protocol = FULL;
            Mode = PMUCRU;
            break;
        case 4:
            mode_pll_protocol = SHUTDOWN_ONLY;
            Mode = PMUCRU;
            break;
        default:
            rcmd->From = 0x01U;
            rcmd->ShortResponse = 0x02U;
            rcmd->CauseSyndrome = 0xBBU;
            rcmd->Syndrome = 0x11U;
            break;
    }
    
    clk_cru_pll_conf_rk3399(cmd, mode_pll_protocol, rcmd);
    rcmd->From = 0x01U;
}


void clk_cru_conf_sel_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info, unzero_rcmd_t* rcmd){
    uint8_t itteration = ((*reg_info >> 48) & 0xFF);
    UZRCMD_CHECKF_ITERATION(rcmd, 0x01U, 0x11U, 0U, 4U, itteration);

    uint8_t size_div, current_pll, current_div_bit, current_pll_bit, mask_pll = 0x0;
    uint16_t current_div, mask_div = 0x0;
    uint16_t current_offset = 0x0;
    volatile uint32_t* SEL = 0x0;
    volatile uint32_t orig = 0x0;
    switch(Mode){
        case BASECRU:
            SEL = (volatile uint32_t*)0xFF760000;
            orig = 0xFF760000;
            break;
        case PMUCRU:
            SEL = (volatile uint32_t*)0xFF750000;
            orig = 0xFF750000;
            break;
    }

    for(int index = 0; index < itteration; index++){
        size_div = (*field_info >> ((index * 4) + 32)) & 0xF;

        current_pll = (*cmd >> ((index * 3) + 32)) & 0x7; 

        current_div_bit = (*field_info >> (index * 4)) & 0xF;
        current_pll_bit = (*field_info >> ((index * 4) + 16)) & 0xF;

        mask_div = (*mask_info >> (index * 12)) & 0xFFF;
        mask_pll = (*mask_info >> ((index * 3) + 48)) & 0x7;

        current_div = (*cmd >> (index * size_div)) & mask_div;
        current_offset = (*reg_info >> (index * 12)) & 0xFFF;
        SEL = (volatile uint32_t*)((volatile uint32_t)SEL + current_offset);

        *SEL = (current_div << current_div_bit) | (current_pll << current_pll_bit) | (mask_div << (current_div_bit + 16)) | (mask_pll << (current_pll_bit + 16));
        
        SEL = (volatile uint32_t*)orig;
    }
}

void clk_cru_conf_gate_reset_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, unzero_rcmd_t* rcmd){
    uint8_t itteration = ((*reg_info >> 48) & 0xFF);
    UZRCMD_CHECKF_ITERATION(rcmd, 0x01U, 0x11U, 0U, 4U, itteration);
    
    uint16_t mask_gate, current_gate, current_offset = 0x0;
    uint8_t current_gate_bit = 0x0;
    volatile uint32_t* SEL = 0x0;
    volatile uint32_t orig = 0x0;
    switch(Mode){
        case BASECRU:
            SEL = (volatile uint32_t*)0xFF760000;
            orig = 0xFF760000;
            break;
        case PMUCRU:
            SEL = (volatile uint32_t*)0xFF750000;
            orig = 0xFF750000;
            break;
    }

    for(int index = 0; index < itteration; index++){
        current_gate = (*cmd >> (8 * index)) & 0xFF;
        current_gate_bit = (*field_info >> (4 * index)) & 0xF;
        mask_gate = (*field_info >> ((8 * index) + 16) & 0xFF);

        current_offset = (*reg_info >> (index * 12)) & 0xFFF;
        SEL = (volatile uint32_t*)((volatile uint32_t)SEL + current_offset);

        *SEL = (current_gate << current_gate_bit) | (mask_gate << (current_gate_bit + 16));
        
        SEL = (volatile uint32_t*)orig;
    }
}

void clk_cru_conf_other_register(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, unzero_rcmd_t* rcmd){
    uint8_t itteration = ((*reg_info >> 48) & 0x3);
    UZRCMD_CHECKF_ITERATION(rcmd, 0x01U, 0x11U, 0U, 2U, itteration);
    
    uint16_t mask_other, current_other, current_offset = 0x0;
    uint8_t current_other_bit = 0x0;
    volatile uint32_t* SEL = 0x0;
    volatile uint32_t orig = 0x0;
    switch(Mode){
        case BASECRU:
            SEL = (volatile uint32_t*)0xFF760000;
            orig = 0xFF760000;
            break;
        case PMUCRU:
            SEL = (volatile uint32_t*)0xFF750000;
            orig = 0xFF750000;
            break;
    }

    for(int index = 0; index < itteration; index++){
        current_other = (*cmd >> (16 * index)) & 0xFFFF;
        current_other_bit = (*field_info >> (4 * index)) & 0xF;
        mask_other = (*field_info >> ((16 * index) + 8) & 0xFFFF);

        current_offset = (*reg_info >> (index * 12)) & 0xFFF;
        SEL = (volatile uint32_t*)((volatile uint32_t)SEL + current_offset);

        *SEL = (current_other << current_other_bit) | (mask_other << (current_other_bit + 16));
        
        SEL = (volatile uint32_t*)orig;
    }
}

void clk_cru_pll_conf_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode, unzero_rcmd_t* rcmd){
    uint16_t feedback = (*cmd & 0x7FF);
    uint16_t offset = ((*cmd >> 12) & 0xFF);
    uint8_t ref_div = (*cmd >> 28) & 0x3F;
    uint8_t post_div1 = (*cmd >> 34) & 0x7;
    uint8_t post_div2 = (*cmd >> 37) & 0x7;
    
    clk_cru_pll_pattern_t* pll;
    switch(Mode){
        case BASECRU:
            pll = (clk_cru_pll_pattern_t*)(0xFF760000 + ((*cmd >> 12) & 0xFF));
            break;
        case PMUCRU:
            pll = (clk_cru_pll_pattern_t*)(0xFF750000 + ((*cmd >> 12) & 0xFF));
            break;
    }

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