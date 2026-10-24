#pragma once

#include<stdint.h>

typedef enum{
    BIT32,
    BIT36,
    BIT40,
    BIT42,
    BIT44,
    BIT48,
    BIT52,
    BIT56
}mmu_ps_e;

typedef enum{
    KB4,
    KB64,
    KB16
}mmu_tg_t;

typedef enum{
    ATTR0,
    ATTR1,
    ATTR2,
    ATTR3,
    ATTR4,
    ATTR5,
    ATTR6,
    ATTR7
}mmu_attr_index_e;

typedef struct{
    uint64_t MaxDesciprot;
    uint64_t L1Plus;
    uint64_t L2Plus;
    uint64_t T0SZ;
    mmu_tg_t TG;
}mmu_data_about_table_t;