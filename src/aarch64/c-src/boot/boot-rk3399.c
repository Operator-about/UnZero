#include<Clk-CRU-rk3399.h>
#include<PMU-PMU-rk3399.h>
#include<GIC-GICv3.h>
#include<ustd.h>
#include<UART165050A.h>
#include<MMU.h>


extern void jump_to_elxh(uint64_t jump_point, uint64_t ns, uint64_t el_dist);

void main(void){
    UART165050A_Synops = (uart_165050A_synops_t*)0xFF1A0000;
    uart165050A_init(0U, 1U);
    uprintf("[UnZero]UART2 on rk3399 in operation's\r\n");

    mmu_conf_ips36_and_lower(BIT32, 0xC0000000, 4ULL);
    uprintf("[UnZero]MMU on rk3399 in operation's\r\n");

    CRU = (clk_cru_rk3399_t*)0xFF760000;
    PMU = (pmu_pmu_rk3399_t*)0xFF310000;
    PMU_CRU = (clk_pmucru_rk3399_t*)0xFF750000;

    GICD = (gic_gicd_t*)0xFEE00000;
    GICR = (gic_gicr_t*)0xFEF00000;

    uint64_t cmd_gpll = 0x0;
    cmd_gpll = (1ULL << 56) | (0ULL << 48) | (0x47ULL << 40) | (1ULL << 37) | (1ULL << 34) | (4ULL << 28) | (0x0080ULL << 12) | (99ULL << 0);
    clk_cru_pll_conf_rk3399(&cmd_gpll, FULL);
    uprintf("[UnZero]GPLL on rk3399 in operation's\r\n");
    
    uint64_t cmd = 0x0;
    uint64_t field_info = 0x0;
    uint64_t reg_info = 0x0;
    uint64_t mask_info = 0x0;

    Mode = BASECRU;

    //UART Synops
    cmd = (3ULL << 48) | (1ULL << 0);
    field_info = (0x1ULL << 16) | (4ULL << 0);
    reg_info = (1ULL << 32) | (9ULL << 0);
    clk_cru_conf_gate_rk3399(&cmd, &field_info, &reg_info);

    cmd = (1ULL << 48) | (0ULL << 35) | (1ULL << 32) | (24ULL << 8) | (0ULL << 0);
    field_info = (8ULL << 20) | (15ULL << 16) | (0ULL << 4) | (0ULL << 0);
    reg_info = (2ULL << 32) | (35ULL << 8) | (33ULL << 0);
    mask_info = (0x3ULL << 51) | (0x1ULL << 48) | (0x7FULL << 12) | (0x0ULL << 0);
    clk_cru_conf_sel_rk3399(&cmd, &field_info, &reg_info, &mask_info, 8U);

    cmd = (3ULL << 48) | (0ULL << 0);
    field_info = (0x1ULL << 16) | (4ULL << 0);
    reg_info = (1ULL << 32) | (9ULL << 0);
    clk_cru_conf_gate_rk3399(&cmd, &field_info, &reg_info);

    uart165050A_init(0U, 1U);
    uprintf("[UnZero]New Clk to UART2 on rk3399 in operation's\r\n");
    uprintf("[UnZero]re-init UART2 on rk3399 in done\r\n");
    uprintf("[UnZero]UART2 on rk3399 in operation's\r\n");
    
    //GIC-500
    cmd = (0x3FULL << 8) | (1ULL << 0);
    field_info = (0x3FULL << 16) | (0x1ULL << 16) | (12ULL << 4) | (0ULL << 0);
    reg_info = (2ULL << 32) | (33ULL << 8) | (22ULL << 0);
    clk_cru_conf_gate_rk3399(&cmd, &field_info, &reg_info);

    cmd = (1ULL << 32) | (1ULL << 0);
    field_info = (15ULL << 16) | (8ULL << 0);
    reg_info = (1ULL << 32) | (56ULL << 0);
    mask_info = (0x1ULL << 48) | (0x1FULL << 0);
    clk_cru_conf_sel_rk3399(&cmd, &field_info, &reg_info, &mask_info, 8U);

    cmd = (0ULL << 8) | (0ULL << 0);
    field_info = (0x3FULL << 16) | (0x1ULL << 16) | (12ULL << 4) | (0ULL << 0);
    reg_info = (2ULL << 32) | (33ULL << 8) | (22ULL << 0);
    clk_cru_conf_gate_rk3399(&cmd, &field_info, &reg_info);

    uint64_t cmd_gic = 0x0;
    cmd_gic = (0x7ULL << 0) | (0x3ULL << 4);
    gic_gicd_ctlr_conf(&cmd_gic);

    cmd_gic = ((~0x7ULL) << 24);
    gic_gicr_ctlr_conf(&cmd_gic);
    gic_gicr_wakerw_conf();

    cmd_gic = (0xFULL << 0);
    gic_icc_sre_conf(&cmd_gic);

    cmd_gic = (0xFFULL << 0);
    gic_icc_pmr_conf(&cmd_gic);

    cmd_gic = (0x3ULL << 0);
    gic_icc_igrpen1_conf(&cmd_gic);

    cmd_gic = (1ULL << 6);
    gic_icc_ctlr_conf(&cmd_gic);
    uprintf("[UnZero]GIC-500 on rk3399 in operation's\r\n");

    uprintf("[UnZero]Jump to next boot stage\r\n");

    jump_to_elxh(0x02000000, (uint64_t)(9ULL << 0), (uint64_t)(1ULL << 0));
}