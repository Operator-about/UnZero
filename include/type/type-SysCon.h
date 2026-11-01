#pragma once

#include<stdint.h>
#include<stdalign.h>

typedef enum{
    BASEGRF,
    PMUGRF
}syscon_mode_e;

typedef struct{
    void (*syscon_handle)(uint64_t* cmd, uint64_t* conf);
}syscon_hal_t;

extern alignas(8) syscon_hal_t Syscon_HAL;