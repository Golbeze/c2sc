ENTRY(main)
SECTIONS {
    .shellcode : {
        /tmp/output.o (.text*.main)
        /tmp/output.o (.text*)
        /tmp/output.o (.rodata*)
        /tmp/output.o (.data*)
        /tmp/output.o (.bss*)
    }
    
    /DISCARD/ : {
        *(.interp)
        *(.dynsym)
        *(.dynstr)
        *(.hash)
        *(.gnu.hash)
        *(.header)
        *(.comment)
    }
}
