#include<Clk-CRU-rk3399.h>

clk_pmucru_rk3399_t* PMU_CRU;
clk_cru_rk3399_t* CRU;
clk_cru_mode_rk3399_t Mode;

void clk_cru_handle_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info){
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
            clk_cru_conf_gate_rk3399(cmd, field_info, reg_info);
            break;
        case 4:
            clk_cru_conf_reset_rk3399(cmd, field_info, reg_info);
            break;
        case 1:
            clk_cru_conf_sel_rk3399(cmd, field_info, reg_info, mask_info);
            break;
        default:
            break;
    }
}

void clk_cru_pll_handle_rk3399(uint64_t* cmd){
    clk_cru_pll_seq_mode_rk3399_e mode = FULL;
    switch((*cmd >> 48) & 0xFF){
        case 0:
            mode = FULL;
            break;
        case 1:
            mode = SHUTDOWN_ONLY;
            break;
        default:
            break;
    }
    
    switch((*cmd >> 40) & 0xFF){
        case 'G':
            clk_cru_gpll_rk3399(cmd, mode);
            break;
        case 'L':
            clk_cru_lpll_rk3399(cmd, mode);
            break;
        case 'P':
            clk_cru_ppll_rk3399(cmd, mode);
            break;
        case 'B':
            clk_cru_bpll_rk3399(cmd, mode);
            break;
        case 'C':
            clk_cru_cpll_rk3399(cmd, mode);
            break;
        case 'D':
            clk_cru_dpll_rk3399(cmd, mode);
            break;
        case 'V':
            clk_cru_vpll_rk3399(cmd, mode);
            break;
        case 'N':
            clk_cru_npll_rk3399(cmd, mode);
            break;
        default:
            break;
    }
}

void clk_cru_conf_sel_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info){
    for(int index = 0; index < ((*reg_info >> 32) & 0xFF); index++){
        uint16_t current_div = (*cmd >> (index * 8)) & 0xFF;
        uint8_t current_pll = (*cmd >> 32) & 0x7; 
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

void clk_cru_conf_gate_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info){
    for(int index = 0; index < ((*reg_info >> 32) & 0xFF); index++){
        uint16_t current_gate = (*cmd >> (8 * index)) & 0xFF;
        uint16_t current_gate_bit = (*field_info >> (4 * index)) & 0xF;
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

void clk_cru_conf_reset_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info){
    for(int index = 0; index < ((*reg_info >> 32) & 0xFF); index++){
        uint16_t current_reset = (*cmd >> (8 * index)) & 0xFF;
        uint16_t current_reset_bit = (*field_info >> (4 * index)) & 0xF;
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

void clk_cru_gpll_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode){
    uint16_t feedback = (*cmd & 0x7FF);
    uint8_t ref_div = (*cmd >> 28) & 0x3F;
    uint8_t post_div1 = (*cmd >> 34) & 0x7;
    uint8_t post_div2 = (*cmd >> 37) & 0x7;
    switch(mode){
        case FULL:
            CRU->GPLL[0] = (feedback << 0) | (0x7FFU << 16);
            CRU->GPLL[1] = (ref_div << 0) | (post_div1 << 8) | (post_div2 << 12) | (0x3F << 16) | (0x7 << 24) | (0x7 << 28);
            CRU->GPLL[3] = (0U << 0) | (1U << 8) | (0x1U << 16) | (0x3U << 24);

            while((CRU->GPLL[2] & (1U << 31)) == 0){
                __asm__("NOP");
            }
            break;
        case SHUTDOWN_ONLY:
            CRU->GPLL[3] = (1U << 0) | (0x1U << 16);
            break;
    }
}

void clk_cru_bpll_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode){
    uint16_t feedback = (*cmd & 0x7FF);
    uint8_t ref_div = (*cmd >> 28) & 0x3F;
    uint8_t post_div1 = (*cmd >> 34) & 0x7;
    uint8_t post_div2 = (*cmd >> 37) & 0x7;
    switch(mode){
        case FULL:
            CRU->BPLL[0] = (feedback << 0) | (0x7FFU << 16);
            CRU->BPLL[1] = (ref_div << 0) | (post_div1 << 8) | (post_div2 << 12) | (0x3F << 16) | (0x7 << 24) | (0x7 << 28);
            CRU->BPLL[3] = (0U << 0) | (1U << 8) | (0x1U << 16) | (0x3U << 24);

            while((CRU->BPLL[2] & (1U << 31)) == 0){
                __asm__("NOP");
            }
            break;
        case SHUTDOWN_ONLY:
            CRU->BPLL[3] = (1U << 0) | (0x1U << 16);
            break;
    }
}

void clk_cru_lpll_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode){
    uint16_t feedback = (*cmd & 0x7FF);
    uint8_t ref_div = (*cmd >> 28) & 0x3F;
    uint8_t post_div1 = (*cmd >> 34) & 0x7;
    uint8_t post_div2 = (*cmd >> 37) & 0x7;
    switch(mode){
        case FULL:
            CRU->LPLL[0] = (feedback << 0) | (0x7FFU << 16);
            CRU->LPLL[1] = (ref_div << 0) | (post_div1 << 8) | (post_div2 << 12) | (0x3F << 16) | (0x7 << 24) | (0x7 << 28);
            CRU->LPLL[3] = (0U << 0) | (1U << 8) | (0x1U << 16) | (0x3U << 24);

            while((CRU->LPLL[2] & (1U << 31)) == 0){
                __asm__("NOP");
            }
            break;
        case SHUTDOWN_ONLY:
            CRU->LPLL[3] = (1U << 0) | (0x1U << 16);
            break;
    }
}

void clk_cru_ppll_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode){
    uint16_t feedback = (*cmd & 0x7FF);
    uint8_t ref_div = (*cmd >> 28) & 0x3F;
    uint8_t post_div1 = (*cmd >> 34) & 0x7;
    uint8_t post_div2 = (*cmd >> 37) & 0x7;
    switch(mode){
        case FULL:
            PMU_CRU->PPLL[0] = (feedback << 0) | (0x7FFU << 16);
            PMU_CRU->PPLL[1] = (ref_div << 0) | (post_div1 << 8) | (post_div2 << 12) | (0x3F << 16) | (0x7 << 24) | (0x7 << 28);
            PMU_CRU->PPLL[3] = (0U << 0) | (1U << 8) | (0x1U << 16) | (0x3U << 24);

            while((PMU_CRU->PPLL[2] & (1U << 31)) == 0){
                __asm__("NOP");
            }
            break;
        case SHUTDOWN_ONLY:
            PMU_CRU->PPLL[3] = (1U << 0) | (0x1U << 16);
            break;
    }
}

void clk_cru_cpll_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode){
    uint16_t feedback = (*cmd & 0x7FF);
    uint8_t ref_div = (*cmd >> 28) & 0x3F;
    uint8_t post_div1 = (*cmd >> 34) & 0x7;
    uint8_t post_div2 = (*cmd >> 37) & 0x7;
    switch(mode){
        case FULL:
            CRU->CPLL[0] = (feedback << 0) | (0x7FFU << 16);
            CRU->CPLL[1] = (ref_div << 0) | (post_div1 << 8) | (post_div2 << 12) | (0x3F << 16) | (0x7 << 24) | (0x7 << 28);
            CRU->CPLL[3] = (0U << 0) | (1U << 8) | (0x1U << 16) | (0x3U << 24);

            while((CRU->CPLL[2] & (1U << 31)) == 0){
                __asm__("NOP");
            }
            break;
        case SHUTDOWN_ONLY:
            CRU->CPLL[3] = (1U << 0) | (0x1U << 16);
            break;
    }
}

void clk_cru_vpll_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode){
    uint16_t feedback = (*cmd & 0x7FF);
    uint8_t ref_div = (*cmd >> 28) & 0x3F;
    uint8_t post_div1 = (*cmd >> 34) & 0x7;
    uint8_t post_div2 = (*cmd >> 37) & 0x7;
    switch(mode){
        case FULL:
            CRU->VPLL[0] = (feedback << 0) | (0x7FFU << 16);
            CRU->VPLL[1] = (ref_div << 0) | (post_div1 << 8) | (post_div2 << 12) | (0x3F << 16) | (0x7 << 24) | (0x7 << 28);
            CRU->VPLL[3] = (0U << 0) | (1U << 8) | (0x1U << 16) | (0x3U << 24);

            while((CRU->VPLL[2] & (1U << 31)) == 0){
                __asm__("NOP");
            }
            break;
        case SHUTDOWN_ONLY:
            CRU->VPLL[3] = (1U << 0) | (0x1U << 16);
            break;
    }
}

void clk_cru_npll_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode){
    uint16_t feedback = (*cmd & 0x7FF);
    uint8_t ref_div = (*cmd >> 28) & 0x3F;
    uint8_t post_div1 = (*cmd >> 34) & 0x7;
    uint8_t post_div2 = (*cmd >> 37) & 0x7;
    switch(mode){
        case FULL:
            CRU->NPLL[0] = (feedback << 0) | (0x7FFU << 16);
            CRU->NPLL[1] = (ref_div << 0) | (post_div1 << 8) | (post_div2 << 12) | (0x3F << 16) | (0x7 << 24) | (0x7 << 28);
            CRU->NPLL[3] = (0U << 0) | (1U << 8) | (0x1U << 16) | (0x3U << 24);

            while((CRU->NPLL[2] & (1U << 31)) == 0){
                __asm__("NOP");
            }
            break;
        case SHUTDOWN_ONLY:
            CRU->NPLL[3] = (1U << 0) | (0x1U << 16);
            break;
    }
}

void clk_cru_dpll_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode){
    uint16_t feedback = (*cmd & 0x7FF);
    uint8_t ref_div = (*cmd >> 28) & 0x3F;
    uint8_t post_div1 = (*cmd >> 34) & 0x7;
    uint8_t post_div2 = (*cmd >> 37) & 0x7;
    switch(mode){
        case FULL:
            CRU->DPLL[0] = (feedback << 0) | (0x7FFU << 16);
            CRU->DPLL[1] = (ref_div << 0) | (post_div1 << 8) | (post_div2 << 12) | (0x3F << 16) | (0x7 << 24) | (0x7 << 28);
            CRU->DPLL[3] = (0U << 0) | (1U << 8) | (0x1U << 16) | (0x3U << 24);

            while((CRU->DPLL[2] & (1U << 31)) == 0){
                __asm__("NOP");
            }
            break;
        case SHUTDOWN_ONLY:
            CRU->DPLL[3] = (1U << 0) | (0x1U << 16);
            break;
    }
}

alignas(8) clk_hal_t CLK_HAL = {
    .clk_conf_mux = &clk_cru_conf_sel_rk3399,
    .clk_conf_gate = &clk_cru_conf_gate_rk3399,
    .clk_conf_reset = &clk_cru_conf_reset_rk3399,
    .clk_handle = &clk_cru_handle_rk3399,
    .clk_pll_handle = &clk_cru_pll_handle_rk3399
};