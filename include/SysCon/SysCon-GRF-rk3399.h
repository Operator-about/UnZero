#pragma once

#include<type-SysCon.h>

void syscon_grf_handle_rk3399(uint64_t* cmd, uint64_t* conf);
void syscon_grf_with_mask_conf_rk3399(uint64_t* cmd, uint64_t* conf, syscon_mode_e mode);
void syscon_grf_without_mask_conf_rk3399(uint64_t* cmd, uint64_t* conf, syscon_mode_e mode);