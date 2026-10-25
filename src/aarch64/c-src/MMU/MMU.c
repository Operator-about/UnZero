#include<MMU.h>

alignas(4096) uint64_t L0[1][512];
alignas(4096) uint64_t L1[512][512];
alignas(8) uint64_t Current_address;

void mmu_conf_ips36_and_lower(mmu_ps_e ps, uint64_t device_border, uint32_t itteration){
    Current_address = 0x0;

    mmu_l_table_lookup_conf(512, L0, (uint64_t)&L1[0], 0ULL, 0ULL);

    for(int current_descriptor = 0; current_descriptor < itteration; current_descriptor++){
        if(Current_address >= device_border && Current_address < (device_border + 0x40000000)){
            mmu_l_table_block_conf_once(512, L1, 0x40000000, ATTR0, 0ULL, current_descriptor);
        }
        else{
            mmu_l_table_block_conf_once(512, L1, 0x40000000, ATTR1, 0ULL, current_descriptor);
        }
    }

    mmu_reg_conf(KB4, ps);
}

void mmu_conf_ips40_and_higer(mmu_ps_e ps, uint64_t device_border, uint32_t itteration){
    Current_address = 0x0;

    for(int current_table = 0; current_table < itteration; current_table++){
        mmu_l_table_lookup_conf(512, L0, (uint64_t)&L1[current_table], 0U, current_table);

        mmu_l_table_block_conf(512, L1, 0x40000000, &device_border, ATTR1, ATTR0, 512, &current_table);
    }
    
    mmu_reg_conf(KB4, ps);
}

void mmu_reg_conf(mmu_tg_t tg, mmu_ps_e ps){
    uint64_t tcr;
    uint64_t ttbr0;
    uint64_t mair;
    uint64_t sctlr;

    tcr = (ps << 16) | (tg << 14) | (16ULL << 0);
    mair = (4ULL << 0) | (68ULL << 8);
    sctlr = (1ULL << 0);

    ttbr0 = ((uint64_t)&L0 << 0);

    __asm__("MSR TTBR0_EL3, %0" : :"r"(ttbr0));
    __asm__("MSR TCR_EL3, %0" : :"r"(tcr));
    __asm__("MSR MAIR_EL3, %0" : :"r"(mair));

    __asm__("DSB SY");
    __asm__("ISB");

    __asm__("MSR SCTLR_EL3, %0" : :"r"(sctlr));
    __asm__("DSB SY");
    __asm__("ISB");

    __asm__("LDR X1, =vector_table");
    __asm__("MSR VBAR_EL3, X1");
    __asm__("DSB SY");
    __asm__("ISB");
}

void mmu_l_table_block_conf(int count_desc, uint64_t l_table[][count_desc], uint64_t l_plus, uint64_t* device_border, mmu_attr_index_e attr_normal, mmu_attr_index_e attr_device, uint32_t itteration, uint32_t* current_table){
    for(int descriptor_index = 0U; descriptor_index < itteration; descriptor_index++){
        l_table[*current_table][descriptor_index] = Current_address;
        l_table[*current_table][descriptor_index] |= (1ULL << 0);
        l_table[*current_table][descriptor_index] &= ~(1ULL << 1);
        if(Current_address >= *device_border && Current_address < (*device_border + 0x40000000)){
            l_table[*current_table][descriptor_index] |= (attr_normal << 2);
        }
        else{
            l_table[*current_table][descriptor_index] |= (attr_device << 2);
        }
        l_table[*current_table][descriptor_index] &= ~(3ULL << 6);
        l_table[*current_table][descriptor_index] &= ~(3ULL << 8);
        l_table[*current_table][descriptor_index] |= (1ULL << 10);
        Current_address += l_plus;
    }
}

void mmu_l_table_lookup_conf(int count_desc, uint64_t l_table[][count_desc], uint64_t l_look_up_address, uint32_t current_table, uint32_t current_desc){
    l_table[current_table][current_desc] = l_look_up_address;
    l_table[current_table][current_desc] |= (1ULL << 0) | (1ULL << 1) | (1ULL << 10);
}

void mmu_l_table_block_conf_once(int count_desc, uint64_t l_table[][count_desc], uint64_t l_plus, mmu_attr_index_e attr, uint32_t current_table, uint32_t current_desc){
    l_table[current_table][current_desc] = Current_address;
    l_table[current_table][current_desc] |= (1ULL << 0);
    l_table[current_table][current_desc] &= ~(1ULL << 1);
    l_table[current_table][current_desc] |= (attr << 2);
    l_table[current_table][current_desc] &= ~(3ULL << 6);
    l_table[current_table][current_desc] &= ~(3ULL << 8);
    l_table[current_table][current_desc] |= (1ULL << 10);
    Current_address += l_plus;
}