#pragma once

#include<stdint.h>

typedef enum{
    ERROR,
    WARNING,
    SUCCESS
}unzero_status_e;

typedef struct{
    uint8_t ShortResponse;
    uint8_t Syndrome;
    uint8_t CauseSyndrome;
    uint8_t From;
    unzero_status_e Status;
}unzero_rcmd_t;