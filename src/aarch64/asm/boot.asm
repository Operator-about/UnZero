.section ".text.boot", "ax"
.global boot

boot:
    MOV X10, X0

    LDR X0, =vector_table
    MSR VBAR_EL3, X0

    LDR X0, =EL3h_SP_bottom
    MOV SP, X0

    B main

.section .text
.global main
.global jump

jump:
    MOV X0, XZR
    MRS X0, SCR_EL3
    ORR X0, X0, #(1ULL << 10)
    AND X0, X0, #~(1ULL << 1)
    ORR X0, X0, #(1ULL << 0)
    MSR SCR_EL3, X0

    MOV X0, XZR
    MOV X0, #(9ULL << 0)
    AND X0, X0, #~(1ULL << 4)
    ORR X0, X0, #(1ULL << 7)
    MSR SPSR_EL3, X0

    LDR X0, =EL2h_SP_bottom
    MSR SP_EL2, X0

    LDR X0, =0x00200000
    //LDR X0, =test
    MSR ELR_EL3, X0

    MOV X0, X10
    ERET
    
.section .bss
.align 4
EL3h_SP_top:
    .SPACE 4096
EL3h_SP_bottom:
.align 4
EL2h_SP_top:
    .SPACE 1024
EL2h_SP_bottom: