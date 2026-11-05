#include<UnZero-RCMD.h>

void unzero_rcmd_bit_check(unzero_rcmd_t* rcmd, uint8_t max_bit, uint8_t* src){
    if(*src > max_bit){
        *rcmd = (unzero_rcmd_t){.ShortResponse = 2U, .CauseSyndrome = 0x32U, .Status = ERROR};
    }
}

void unzero_rcmd_value_check(unzero_rcmd_t* rcmd, uint16_t max_value, uint16_t war_value, uint16_t* src){
    if(*src >= max_value){
        *rcmd = (unzero_rcmd_t){.ShortResponse = 2U, .CauseSyndrome = 0x11U, .Status = ERROR};
    }
    else if(*src >= war_value && *src < (max_value - 1)){
        *rcmd = (unzero_rcmd_t){.ShortResponse = 1U, .CauseSyndrome = 0x41U, .Status = WARNING};
    }
}

void unzero_rcmd_offset_check(unzero_rcmd_t* rcmd, uint32_t max_addess, uint16_t* src){
    if((*src + max_addess) > max_addess){
        *rcmd = (unzero_rcmd_t){.ShortResponse = 2U, .CauseSyndrome = 0xAAU, .Status = ERROR};
    }
}

void unzero_rcmd_itteration_check(unzero_rcmd_t* rcmd, uint8_t max_itteration, uint8_t* src){
    if(*src >= max_itteration){
        *rcmd = (unzero_rcmd_t){.ShortResponse = 2U, .CauseSyndrome = 0x31U, .Status = ERROR};
    }
}