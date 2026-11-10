#pragma once

#include<type-PMU.h>
#include<Clk-CRU-rk3399.h>
#include<UnZero-RCMD.h>

extern pmu_pmu_rk3399_t* PMU;

void pmu_pmu_pwrdn_rk3399(uint8_t pwrdn_bit, pmu_mode_e mode);
void pmu_pmu_bus_rk3399(uint8_t bus_bit, pmu_mode_e mode);

void pmu_pmu_handle_rk3399(uint64_t* cmd);
void pmu_pmu_pwrdn_handle_rk3399(uint8_t hex_code, pmu_mode_e mode);
void pmu_pmu_bus_handle_rk3399(uint8_t hex_code, pmu_mode_e mode);
void pmu_clk_handle_rk3399(uint8_t hex_code, pmu_mode_e mode);

void pmu_clk_gic_conf_rk3399();