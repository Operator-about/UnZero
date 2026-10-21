#include<GIC-GICv3.h>

gic_gicd_t* GICD;
gic_gicr_t* GICR;

void gic_irq_conf(uint64_t* cmd, uint64_t* afe){
    uint8_t id = *cmd & 0xFFFF;
    uint8_t priority = (*cmd >> 16) & 0xFF;
    
    GICD->IGROUPER[id / 32] &= ~(1U << (id % 32));
    GICD->IGROUPER[id / 32] |= (((*cmd >> 26) & 0x1) << (id % 32));

    GICD->IGRPMODR[id / 32] &= ~(1U << (id % 32));
    GICD->IGRPMODR[id / 32] |= (((*cmd >> 27) & 0x1) << (id % 32));

    GICD->ICFGR[id / 16] &= ~(3U << ((id % 16) * 2));
    GICD->ICFGR[id / 16] |= (((*cmd >> 24) & 0x3) << ((id % 16) * 2));

    GICD->IPRIORITYR[id / 4] &= ~(0xFF << ((id % 4) * 8));
    GICD->IPRIORITYR[id / 4] |= (((*cmd >> 16) & 0xFF) << ((id % 4) * 8));

    GICD->IROUTER[id] = ((*afe & 0xFF) << 0) | (((*afe >> 8) & 0xFF) << 8) | (((*afe >> 16) & 0xFF) << 16) | (((*afe >> 24) & 0xFF) << 32) | (0ULL << 31);

    GICD->ISENABLER[id / 32] &= ~(1U << (id % 32));
    GICD->ISENABLER[id / 32] |= (1U << (id % 32));
}

void gic_gicd_ctlr_conf(uint64_t* conf){
    GICD->CTLR |= *conf & 0xFFFFFFFF;
}

void gic_gicr_ctlr_conf(uint64_t* conf){
    GICR->CTLR = *conf & 0xFFFFFFFF;
}

void gic_gicr_wakerw_conf(){
    GICR->WAKER &= ~(1U << 1);
    while(GICR->WAKER & (1U << 1)){
        __asm__("NOP");
    }
}

void gic_gicr_wakers_conf(){
    GICR->WAKER |= (1U << 1);
    while((GICR->WAKER & (1U << 1)) == 0){
        __asm__("NOP");
    }
}

void gic_icc_ctlr_conf(uint64_t* conf){
    __asm__("MSR ICC_CTLR_EL3, %0" : :"r"(*conf));
}

void gic_icc_igrpen1_conf(uint64_t* conf){
    __asm__("MSR ICC_IGRPEN1_EL3, %0" : :"r"(*conf));
}

void gic_icc_sre_conf(uint64_t* conf){
    __asm__("MSR ICC_SRE_EL3, %0" : :"r"(*conf));
}

void gic_icc_pmr_conf(uint64_t* conf){
    __asm__("MSR ICC_PMR_EL1, %0" : :"r"(*conf));
}

void gic_handle(uint64_t* cmd, uint64_t* afe, uint64_t* conf){
    switch((*cmd >> 48) & 0xFF){
        case 1:
            gic_irq_conf(cmd, afe);
            break;
        case 2:
            gic_icc_sre_conf(conf);
            break;
        case 3:
            gic_gicd_ctlr_conf(conf);
            break;
        case 4:
            gic_icc_ctlr_conf(conf);
            break;
        case 5:
            gic_icc_pmr_conf(conf);
            break;
        case 8:
            gic_icc_igrpen1_conf(conf);
            break;
        case 9:
            gic_gicr_ctlr_conf(conf);
            break;
        case 10:
            gic_gicr_wakerw_conf();
            break;
        case 11:
            gic_gicr_wakers_conf();
            break;
        default:
            break;
    }
}