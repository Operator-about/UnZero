#pragma once

#include<type-GIC.h>

extern gic_gicd_t* GICD;
extern gic_gicr_t* GICR;

void gic_irq_conf(uint64_t* cmd, uint64_t* afe);
void gic_gicd_ctlr_conf(uint64_t* conf);
void gic_gicr_ctlr_conf(uint64_t* conf);
void gic_gicr_wakerw_conf();
void gic_gicr_wakers_conf();
void gic_icc_ctlr_conf(uint64_t* conf);
void gic_icc_igrpen1_conf(uint64_t* conf);
void gic_icc_sre_conf(uint64_t* conf);
void gic_icc_pmr_conf(uint64_t* conf);
void gic_handle(uint64_t* cmd, uint64_t* afe, uint64_t* conf);