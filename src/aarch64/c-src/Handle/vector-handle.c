#include<vector-handle.h>

void sync_el64th(){
    uprintf("[UnZero]CMD is now progress\r\n");
    
    uint64_t cmd = 0x0;
    uint64_t field_info = 0x0;
    uint64_t reg_info = 0x0;
    uint64_t mask_info = 0x0;
    uint64_t afe = 0x0;
    uint64_t conf = 0x0;
    __asm__("MOV %0, X10" : "=r"(cmd));
    
    switch((cmd >> 56) & 0xFF){
        case 0:
            __asm__("MOV %0, X11" : "=r"(field_info));
            __asm__("MOV %0, X12" : "=r"(reg_info));
            __asm__("MOV %0, X13" : "=r"(mask_info));
            uprintf("[UnZero]CMD for clk\r\n");
            CLK_HAL.clk_handle(&cmd, &field_info, &reg_info, &mask_info);
            break;
        case 1:
            uprintf("[UnZero]CMD for clk PLL\r\n");
            CLK_HAL.clk_pll_handle(&cmd);
            break;     
        case 2:
            __asm__("MOV %0, X11" : "=r"(afe));
            __asm__("MOV %0, X12" : "=r"(conf));
            uprintf("[UnZero]CMD for gic\r\n");
            gic_handle(&cmd, &afe, &conf);
            break;
        case 3:
            uprintf("[UnZero]CMD for pmu\r\n");
            PMU_HAL.pmu_handle(&cmd);
            break;
    }
}