/* filepath: /Users/admin/Desktop/decoder/boot.ld */
ENTRY(start)

SECTIONS
{
    . = 0x7c00;
    
    .text : AT(ADDR(.text)) {
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata.*)
    }
    
    .data : AT(ADDR(.data)) {
        *(.data)
        *(.data.*)
    }
    
    .bss : AT(ADDR(.bss)) {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }
}