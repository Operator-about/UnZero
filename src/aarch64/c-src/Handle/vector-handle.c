#define PLATFORM 1

#include<vector-handle.h>

#include<type-UART.h>
#include<GIC-GICv3.h>

#if PLATFORM == 1

#include<type-Clk.h>
#include<type-PMU.h>
#include<type-SysCon.h>

#endif

#include<ustd.h>

extern void jump_to_elxh(uint64_t jump_point, uint64_t el_dist, uint64_t ns);

void sync_el64th(){
    uprintf("[UnZero]CMD is now progress\r\n");
    
    uint64_t cmd = 0x0;
    uint64_t field_info = 0x0;
    uint64_t reg_info = 0x0;
    uint64_t mask_info = 0x0;
    uint64_t afe = 0x0;
    uint64_t conf = 0x0;
    uint64_t address = 0x0;
    uint64_t rcmd;
    __asm__("MOV %0, X10" : "=r"(cmd));
    
    switch((cmd >> 56) & 0xFF){
        case 0:
            __asm__("MOV %0, X11" : "=r"(field_info));
            __asm__("MOV %0, X12" : "=r"(reg_info));
            __asm__("MOV %0, X13" : "=r"(mask_info));
            uprintf("[UnZero]CMD for clk\r\n");
            #if PLATFORM == 1
                CLK_HAL.clk_handle(&cmd, &field_info, &reg_info, &mask_info, &(unzero_rcmd_t){0});
            #endif
            break;
        case 1:
            uprintf("[UnZero]CMD for clk PLL\r\n");
            #if PLATFORM == 1
                CLK_HAL.clk_pll_handle(&cmd, &(unzero_rcmd_t){0});
            #endif
            break;     
        case 2:
            __asm__("MOV %0, X11" : "=r"(afe));
            __asm__("MOV %0, X12" : "=r"(conf));
            uprintf("[UnZero]CMD for gic\r\n");
            gic_handle(&cmd, &afe, &conf);
            break;
        case 3:
            uprintf("[UnZero]CMD for pmu\r\n");
            #if PLATFORM == 1
                PMU_HAL.pmu_handle(&cmd);
            #endif
            break;
        case 4:
            __asm__("MOV %0, X11" : "=r"(conf));
            uprintf("[UnZero]CMD for GRF\r\n");
            #if PLATFORM == 1
                Syscon_HAL.syscon_handle(&cmd, &conf, &(unzero_rcmd_t){0});
            #endif
            break;
        case 5:
            __asm__("MOV %0, X11" : "=r"(address));
            uprintf("[UnZero]CMD for switch EL context\r\n");
            jump_to_elxh(address, (uint64_t)(cmd & 0xF), (uint64_t)((cmd >> 4) & 0x1));
            break;
    }
}