#pragma once

#include<type-Clk.h>
#include<UnZero-RCMD.h>

extern clk_cru_rk3399_t* CRU;
extern clk_pmucru_rk3399_t* PMU_CRU;
extern clk_cru_mode_rk3399_t Mode;

unzero_rcmd_t clk_cru_conf_sel_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info, uint8_t div_mull);
unzero_rcmd_t clk_cru_conf_gate_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info);
unzero_rcmd_t clk_cru_conf_reset_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info);
void clk_cru_handle_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info, unzero_rcmd_t* rcmd);

void clk_cru_pll_handle_rk3399(uint64_t* cmd, unzero_rcmd_t* rcmd);
unzero_rcmd_t clk_cru_pll_conf_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode);