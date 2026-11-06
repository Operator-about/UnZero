.section .text
.global jump_to_elxh

preparing_elxh:
    LDR X0, =elxh_sp_bottom
    MOV SP, X0

    MOV X0, X3
    BR X0

jump_to_elxh:
    //X0 - Address
    //X1 - EL dist
    //X2 - World mode
    //X3 - Res0
    MOV X3, X0

    MRS X0, SCR_EL3
    AND X0, X0, #~(1ULL << 0)
    ORR X0, X0, X2
    ORR X0, X0, #(1ULL << 10)
    AND X0, X0, #~(1ULL << 1)
    MSR SCR_EL3, X0

    MOV X0, XZR
    ORR X0, X0, X1
    AND X0, X0, #~(1ULL << 4)
    MSR SPSR_EL3, X0

    LDR X0, =preparing_elxh
    MSR ELR_EL3, X0

    ERET

.section .bss
.align 4
elxh_sp_top:
    .SPACE 1024
elxh_sp_bottom: