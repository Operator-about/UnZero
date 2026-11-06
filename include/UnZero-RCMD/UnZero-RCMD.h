#pragma once

#include<type-Other.h>

#define UZRCMD_CHECKF_VALUE(RCMD, FROM, POINT, MAX_VALUE, WAR_VALUE, SRC_VALUE) switch(SRC_VALUE) \
    {case WAR_VALUE ... MAX_VALUE: \
        RCMD->Syndrome = POINT; RCMD->CauseSyndrome = 0x11U; RCMD->From = FROM; RCMD->ShortResponse = 0x02U; return;}

#define UZRCMD_CHECKF_BIT(RCMD, FROM, POINT, MIN_BIT, MAX_BIT, SRC_VALUE) switch(SRC_VALUE) \
    {case MIN_BIT ... MAX_BIT: \
        break; \
    default: \
        RCMD->Syndrome = POINT; RCMD->CauseSyndrome = 0x32U; RCMD->From = FROM; RCMD->ShortResponse = 0x02U; return;}

#define UZRCMD_CHECKF_ITERATION(RCMD, FROM, POINT, MIN_ITERATION, MAX_ITERATION, SRC_VALUE) switch(SRC_VALUE) \
    {case MIN_ITERATION ... MAX_ITERATION: \
        break; \
    default: RCMD->Syndrome = POINT; RCMD->CauseSyndrome = 0x31U; RCMD->From = FROM; RCMD->ShortResponse = 0x02U; return;}

#define UZRCMD_CHECKF_OFFSET(RCMD, FROM, POINT, START_ADDRESS, END_ADDRESS, SRC_VALUE) switch(SRC_VALUE) \
    {case START_ADDRESS ... END_ADDRESS: \
        break; \
    default: RCMD->Syndrome = POINT; RCMD->CauseSyndrome = 0xAAU; RCMD->From = FROM; RCMD->ShortResponse = 0x02U; return;}

void unzero_rcmd_send(unzero_rcmd_t* rcmd);
