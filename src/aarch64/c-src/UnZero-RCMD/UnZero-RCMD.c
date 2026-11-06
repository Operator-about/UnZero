#include<UnZero-RCMD.h>

void unzero_rcmd_send(unzero_rcmd_t* rcmd){
    uint64_t value = (rcmd->From << 20) | (rcmd->CauseSyndrome << 12) | (rcmd->Syndrome << 4) | (rcmd->ShortResponse << 0);
    __asm__("MOV X10, %0" : :"r"(value));
}