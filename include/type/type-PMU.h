#pragma once

#include<stdint.h>
#include<stdalign.h>

typedef struct{
    uint32_t RESERVE_1[5];
    volatile uint32_t PWRDN_CON;
    volatile uint32_t PWRDN_ST;
    uint32_t RESERVE_2[17];
    volatile uint32_t BUS_IDLE_REQ;
    volatile uint32_t BUS_IDLE_ST;
    volatile uint32_t BUS_IDLE_ACK;
}pmu_pmu_rk3399_t;

typedef enum{
    STARTUP,
    SHUTDOWN
}pmu_mode_e;

typedef struct{
    void (*pmu_handle)(uint64_t* cmd);
}pmu_hal_t;

extern alignas(8) pmu_hal_t PMU_HAL;