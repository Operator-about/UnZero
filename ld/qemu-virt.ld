ENTRY(boot)

SECTIONS{
    . = 0x41000000;

    .text : {
        *(.text.boot)
        *(.text)
    }

    . = ALIGN(2048);
    .vector : {
        *(.vector)
    }

    .bss : {
        *(.bss)
    }
}