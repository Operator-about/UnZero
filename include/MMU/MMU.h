#pragma once

#include<type-MMU.h>
#include<stdalign.h>

extern alignas(4096) uint64_t L0[1][512];
extern alignas(4096) uint64_t L1[512][512];
extern alignas(8) uint64_t Current_address;

void mmu_conf_ips36_and_lower(mmu_ps_e ps, uint64_t device_border, uint32_t itteration);
void mmu_conf_ips40_and_higer(mmu_ps_e ps, uint64_t device_border, uint32_t itteration);

void mmu_reg_conf(mmu_tg_t tg, mmu_ps_e ps);
void mmu_l_table_block_conf(int count_desc, uint64_t l_table[][count_desc], uint64_t l_plus, uint64_t* device_border, mmu_attr_index_e attr_normal, mmu_attr_index_e attr_device, uint32_t itteration, uint32_t* current_table);
void mmu_l_table_block_conf_once(int count_desc, uint64_t l_table[][count_desc], uint64_t l_plus, mmu_attr_index_e attr, uint32_t current_table, uint32_t current_desc);
void mmu_l_table_lookup_conf(int count_desc, uint64_t l_table[][count_desc], uint64_t l_look_up_address, uint32_t current_table, uint32_t current_desc);