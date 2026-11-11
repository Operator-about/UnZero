#pragma once

#include<type-Clk.h>
#include<UnZero-RCMD.h>

extern clk_cru_mode_rk3399_t Mode;

void clk_cru_conf_sel_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info, unzero_rcmd_t* rcmd);
void clk_cru_conf_gate_reset_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, unzero_rcmd_t* rcmd);
void clk_cru_conf_other_register(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, unzero_rcmd_t* rcmd);
void clk_cru_handle_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info, unzero_rcmd_t* rcmd);

void clk_cru_pll_handle_rk3399(uint64_t* cmd, unzero_rcmd_t* rcmd);
void clk_cru_pll_conf_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode, unzero_rcmd_t* rcmd);