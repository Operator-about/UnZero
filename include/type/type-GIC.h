#pragma once

#include<stdint.h>

typedef struct{
    volatile uint32_t CTLR;
    uint32_t RESERVE_1[31];
    volatile uint32_t IGROUPER[32];
    volatile uint32_t ISENABLER[32];
    volatile uint32_t ICENABLER[32];
    volatile uint32_t ISPENDER[32];
    volatile uint32_t ICPENDER[32];
    volatile uint32_t ISACTIVER[32];
    volatile uint32_t ICACTIVER[32];
    volatile uint32_t IPRIORITYR[256];
    uint32_t RESERVE_2[256];
    volatile uint32_t ICFGR[64];
    volatile uint32_t IGRPMODR[64];
    uint32_t RESERVE_3[5312];
    volatile uint64_t IROUTER[987];
}gic_gicd_t;

typedef struct{
    volatile uint32_t CTLR;
    uint32_t RESERVE_1[4];
    volatile uint32_t WAKER;
}gic_gicr_t;