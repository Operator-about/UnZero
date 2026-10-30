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
    
.section .bss
.align 4
EL3h_SP_top:
    .SPACE 4096
EL3h_SP_bottom: