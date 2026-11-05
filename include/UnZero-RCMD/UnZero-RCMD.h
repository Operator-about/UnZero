#pragma once

#include<type-Other.h>

#define UZRCMD_CHECKF(syndrome, from, Response) switch(Response->Status) \
    {case ERROR: \
        Response->Syndrome = syndrome; Response->From = from;}

void unzero_rcmd_bit_check(unzero_rcmd_t* rcmd, uint8_t max_bit, uint8_t* src);
void unzero_rcmd_value_check(unzero_rcmd_t* rcmd, uint16_t max_value, uint16_t war_value, uint16_t* src);
void unzero_rcmd_offset_check(unzero_rcmd_t* rcmd, uint32_t max_addess, uint16_t* src);
void unzero_rcmd_itteration_check(unzero_rcmd_t* rcmd, uint8_t max_itteration, uint8_t* src);
