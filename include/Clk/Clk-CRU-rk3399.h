#pragma once

#include<type-Clk.h>

extern clk_cru_rk3399_t* CRU;
extern clk_pmucru_rk3399_t* PMU_CRU;
extern clk_cru_mode_rk3399_t Mode;

void clk_cru_conf_sel_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info, uint8_t div_mull);
void clk_cru_conf_gate_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info);
void clk_cru_conf_reset_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info);
void clk_cru_handle_rk3399(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info);

void clk_cru_pll_handle_rk3399(uint64_t* cmd);
void clk_cru_pll_conf_rk3399(uint64_t* cmd, clk_cru_pll_seq_mode_rk3399_e mode);