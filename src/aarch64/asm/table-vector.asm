.section ".vector", "ax"
.global vector_table
.global irqh
.global sync_el64th

.align 11
vector_table:
    Sync_elxt:
        ERET
    .align 7
    IRQ_elxt:
        ERET
    .align 7
    FIQ_elxt:
        ERET
    .align 7
    SError_elxt:
        ERET
    .align 7
    Sync_elxh:
        ERET
    .align 7
    IRQ_elxh:
        ERET
    .align 7
    FIQ_elxh:
        ERET
    .align 7
    SError_elxh:
        ERET
    .align 7
    Sync_elt64:
        STP X29, X30, [SP, #-16]!

        BL sync_el64th

        LDP X29, X30, [SP], #16
        
        ERET
    .align 7
    IRQ_elt64:
        ERET
    .align 7
    FIQ_elt64:
        ERET
    .align 7
    SError_elt64:
        ERET
    