ENTRY(boot)

SECTIONS{
    . = 0x00020000;

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