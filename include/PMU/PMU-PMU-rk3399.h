#pragma once

#include<Type-PMU.h>
#include<Clk-CRU-rk3399.h>

extern pmu_pmu_rk3399_t* PMU;

void pmu_pmu_pwrdn_e_rk3399(uint8_t pwrdn_bit);
void pmu_pmu_pwrdn_d_rk3399(uint8_t pwrdn_bit);
void pmu_pmu_bus_e_rk3399(uint8_t bus_bit);
void pmu_pmu_bus_d_rk3399(uint8_t bus_bit);
void pmu_pmu_handle_rk3399(uint64_t* cmd);

void pmu_clk_gic_conf_rk3399();