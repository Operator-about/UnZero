#include<UARTPL011.h>
#include<GIC-GICv3.h>
#include<MMU.h>
#include<ustd.h>

extern void jump_to_elxh(uint64_t jump_point, uint64_t ns, uint64_t el_dist);

void main(void){
    UARTPL011_ARM = (uart_pl011_arm_t*)0x09000000;
    uartpl011_init(13U, 1U);

    uprintf("[UnZero]Debug UART on QEMU in operation's\r\n");
    mmu_conf_ips40_and_higer(BIT40, 0x00000000, 2ULL);
    uprintf("[UnZero]MMU on QEMU in operation's\r\n");

    GICD = (gic_gicd_t*)0x08000000;
    GICR = (gic_gicr_t*)0x080A0000;

    uint64_t cmd_gic = 0x0;
    cmd_gic = (0x7ULL << 0) | (0x3ULL << 4);
    gic_gicd_ctlr_conf(&cmd_gic);

    cmd_gic = (0ULL << 24);
    gic_gicr_ctlr_conf(&cmd_gic);
    gic_gicr_wakerw_conf();

    cmd_gic = (0xF << 0);
    gic_icc_sre_conf(&cmd_gic);

    cmd_gic = (0xFF << 0);
    gic_icc_pmr_conf(&cmd_gic);

    cmd_gic = (0x3 << 0);
    gic_icc_igrpen1_conf(&cmd_gic);

    cmd_gic = (1ULL << 6);
    gic_icc_ctlr_conf(&cmd_gic);
    uprintf("[UnZero]GICv3 on QEMU in operation's\r\n");

    uprintf("[UnZero]Jump to next boot stage\r\n");

    jump_to_elxh(0x42000000, (uint64_t)(9ULL << 0), (uint64_t)(1ULL << 0));
}