#include<PMU-PMU-rk3399.h>

pmu_pmu_rk3399_t* PMU;

void pmu_pmu_handle_rk3399(uint64_t* cmd){
    pmu_mode_e mode;
    
    switch((*cmd >> 48) & 0xFF){
        case 1:
            mode = SHUTDOWN;
            break;
        case 2:
            mode = STARTUP;
            break;
    }

    switch((*cmd >> 40) & 0xFF){
        case 0x47:
            switch(mode){
                case STARTUP:
                    pmu_pmu_pwrdn_d_rk3399(29U);
                    pmu_clk_gic_conf_rk3399();
                    pmu_pmu_bus_d_rk3399(27U);
                    break;
                case SHUTDOWN:
                    pmu_pmu_bus_e_rk3399(27U);
                    pmu_pmu_pwrdn_e_rk3399(29U);
                    break;
            }
            break;
    }
}

void pmu_pmu_pwrdn_e_rk3399(uint8_t pwrdn_bit){
    PMU->PWRDN_CON |= (1U << pwrdn_bit);
    while((PMU->PWRDN_ST & (1U << pwrdn_bit)) == 0){
        __asm__("NOP");
    }
}

void pmu_pmu_pwrdn_d_rk3399(uint8_t pwrdn_bit){
    PMU->PWRDN_CON &= ~(1U << pwrdn_bit);
    while(PMU->PWRDN_ST & (1U << pwrdn_bit)){
        __asm__("NOP");
    }
}

void pmu_pmu_bus_e_rk3399(uint8_t bus_bit){
    PMU->BUS_IDLE_REQ |= (1U << bus_bit);
    while((PMU->BUS_IDLE_ST & (1U << bus_bit)) == 0){
        __asm__("NOP");
    }
}

void pmu_pmu_bus_d_rk3399(uint8_t bus_bit){
    PMU->BUS_IDLE_REQ &= ~(1U << bus_bit);
    while(PMU->BUS_IDLE_ACK & (1U << bus_bit)){
        __asm__("NOP");
    }
}

void pmu_clk_gic_conf_rk3399(){
    uint64_t cmd = 0x0;
    uint64_t field_info = 0x0;
    uint64_t reg_info = 0x0;
    uint64_t mask_info = 0x0;

    cmd = (0ULL << 56) | (3ULL << 48) | (0x3FULL << 8) | (0x1ULL << 0);
    field_info = (0x3FULL << 24) | (0x1ULL << 16) | (12ULL << 4) | (0ULL << 0);
    reg_info = (2ULL << 32) | (33ULL << 8) | (12ULL << 0);
    clk_cru_conf_gate_rk3399(&cmd, &field_info, &reg_info);

    //RESET
    cmd = (0ULL << 56) | (4ULL << 48) | (0x1ULL << 8) | (0x1ULL << 0);
    field_info = (0x1ULL << 24) | (0x1ULL << 16) | (12ULL << 4) | (2ULL << 0);
    reg_info = (2ULL << 32) | (10ULL << 8) | (11ULL << 0);
    clk_cru_conf_reset_rk3399(&cmd, &field_info, &reg_info);

    //RESET
    cmd = (0ULL << 56) | (4ULL << 48) | (0x0ULL << 8) | (0x0ULL << 0);
    field_info = (0x1ULL << 24) | (0x1ULL << 16) | (12ULL << 4) | (2ULL << 0);
    reg_info = (2ULL << 32) | (10ULL << 8) | (11ULL << 0);
    clk_cru_conf_reset_rk3399(&cmd, &field_info, &reg_info);

    //SEL GIC-500
    cmd = (0ULL << 56) | (1ULL << 48) | (1ULL << 32) | (1ULL << 0);
    field_info = (15ULL << 16) | (8ULL << 0);
    reg_info = (1ULL << 32) | (56ULL << 0);
    mask_info = (0x1ULL << 48) | (0x1FULL << 0);
    clk_cru_conf_sel_rk3399(&cmd, &field_info, &reg_info, &mask_info, 8U);

    cmd = (0ULL << 56) | (3ULL << 48) | (0ULL << 8) | (0x0ULL << 0);
    field_info = (0x3FULL << 24) | (0x1ULL << 16) | (12ULL << 4) | (0ULL << 0);
    reg_info = (2ULL << 32) | (33ULL << 8) | (12ULL << 0);
    clk_cru_conf_gate_rk3399(&cmd, &field_info, &reg_info);
}

alignas(8) pmu_hal_t PMU_HAL = {
    .pmu_handle = &pmu_pmu_handle_rk3399
};