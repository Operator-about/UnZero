#pragma once

#include<stdint.h>
#include<stdalign.h>

typedef struct{
    volatile uint32_t LPLL[6];
    uint32_t RESERVE_1[2];
    volatile uint32_t BPLL[6];
    uint32_t RESERVE_2[2];
    volatile uint32_t DPLL[6];
    uint32_t RESERVE_3[2];
    volatile uint32_t CPLL[6];
    uint32_t RESERVE_4[2];
    volatile uint32_t GPLL[6];
    uint32_t RESERVE_5[2];
    volatile uint32_t NPLL[6];
    uint32_t RESERVE_6[2];
    volatile uint32_t VPLL[6];
    uint32_t RESERVE_7[10];
    volatile uint32_t CLKSEL_CON[108];
    uint32_t RESERVE_8[20];
    volatile uint32_t CLKGATE_CON[35];
    uint32_t RESERVE_9[29];
    volatile uint32_t CLKRESET_CON[20];
}clk_cru_rk3399_t;

typedef struct{
    volatile uint32_t PPLL[6];
    uint32_t RESERVE_1[26];
    volatile uint32_t CLKSEL_CON[6];
    uint32_t RESERVE_2[26];
    volatile uint32_t CLKGATE_CON[3];
    uint32_t RESERVE_3[1];
    volatile uint32_t CLKRESET_CON[2];
}clk_pmucru_rk3399_t;

typedef struct{
    volatile uint32_t PLL0;
    volatile uint32_t PLL1;
    volatile uint32_t PLL2;
    volatile uint32_t PLL3;
    volatile uint32_t PLL4;
    volatile uint32_t PLL5;
}clk_cru_pll_pattern_t;

typedef enum{
    BASECRU,
    PMUCRU
}clk_cru_mode_rk3399_t;

typedef enum{
    FULL,
    SHUTDOWN_ONLY
}clk_cru_pll_seq_mode_rk3399_e;

typedef struct{
    void (*clk_handle)(uint64_t* cmd, uint64_t* field_info, uint64_t* reg_info, uint64_t* mask_info);
    void (*clk_pll_handle)(uint64_t* cmd);
}clk_hal_t;

extern alignas(8) clk_hal_t CLK_HAL;