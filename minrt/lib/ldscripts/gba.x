/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

OUTPUT_FORMAT(elf32-littlearm)
OUTPUT_ARCH(arm)
ENTRY(_start)
EXTERN(_header)

SECTIONS
{
        /* GBA ROM header */

        .header :
        {
                *(.header)
                __boot_type = 0xC4;
                __boot_client = 0xC5;
        } >LOAD_REGION

        /* Standard code */

        .text :
        {
                *(.text .stub .text.* .gnu.linkonce.t.*)
                *(.gnu.warning)
                *(.glue_7t)
                *(.glue_7)
        } >LOAD_REGION

        /* Standard read-only data */

        .rodata :
        {
                *(.rodata .rodata.* .gnu.linkonce.r.*)
        } >LOAD_REGION

        /* Exception handling and unwinding */

        .ARM.extab :
        {
                *(.ARM.extab* .gnu.linkonce.armextab.*)
        } >LOAD_REGION

        .ARM.exidx :
        {
                PROVIDE_HIDDEN(__exidx_start = .);
                *(.ARM.exidx* .gnu.linkonce.armexidx.*)
                PROVIDE_HIDDEN(__exidx_end = .);
        } >LOAD_REGION

        .eh_frame_hdr :
        {
                *(.eh_frame_hdr)
                *(.eh_frame_entry .eh_frame_entry.*)
        } >LOAD_REGION

        .eh_frame :
        {
                KEEP(*(.eh_frame))
                *(.eh_frame.*)
        } >LOAD_REGION

        .gcc_except_table :
        {
                *(.gcc_except_table .gcc_except_table.*)
        } >LOAD_REGION

        .gnu_extab :
        {
                *(.gnu_extab*)
        } >LOAD_REGION

        /* Static initialization and finalization */

        .init :
        {
                KEEP(*(SORT_NONE(.init)))
        } >LOAD_REGION

        .fini :
        {
                KEEP(*(SORT_NONE(.fini)))
        } >LOAD_REGION

        .preinit_array :
        {
                PROVIDE_HIDDEN(__preinit_array_start = .);
                KEEP (*(.preinit_array))
                PROVIDE_HIDDEN(__preinit_array_end = .);
        } >LOAD_REGION

        .init_array :
        {
                PROVIDE_HIDDEN(__init_array_start = .);
                KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
                KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
                PROVIDE_HIDDEN(__init_array_end = .);
        } >LOAD_REGION

        .fini_array :
        {
                PROVIDE_HIDDEN(__fini_array_start = .);
                KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
                KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
                PROVIDE_HIDDEN(__fini_array_end = .);
        } >LOAD_REGION

        /* IWRAM code/data */

        .iwram :
        {
                *(SORT(.iwram.sorted.*))
                *(.iwram .iwram.*)
        } >EWRAM AT>LOAD_REGION

        OVERLAY : NOCROSSREFS
        {
                .iwram0 { *(.iwram0 .iwram0.*) }
                .iwram1 { *(.iwram1 .iwram1.*) }
                .iwram2 { *(.iwram2 .iwram2.*) }
                .iwram3 { *(.iwram3 .iwram3.*) }
                .iwram4 { *(.iwram4 .iwram4.*) }
                .iwram5 { *(.iwram5 .iwram5.*) }
                .iwram6 { *(.iwram6 .iwram6.*) }
                .iwram7 { *(.iwram7 .iwram7.*) }
                .iwram8 { *(.iwram8 .iwram8.*) }
                .iwram9 { *(.iwram9 .iwram9.*) }
                .iwramA { *(.iwramA .iwramA.*) }
                .iwramB { *(.iwramB .iwramB.*) }
                .iwramC { *(.iwramC .iwramC.*) }
                .iwramD { *(.iwramD .iwramD.*) }
                .iwramE { *(.iwramE .iwramE.*) }
                .iwramF { *(.iwramF .iwramF.*) }
        } >IWRAM AT>LOAD_REGION

        /* EWRAM code/data */

        .ewram :
        {
                *(SORT(.ewram.sorted.*))
                *(.ewram .ewram.*)
        } >EWRAM AT>LOAD_REGION

        OVERLAY : NOCROSSREFS
        {
                .ewram0 { *(.ewram0 .ewram0.*) }
                .ewram1 { *(.ewram1 .ewram1.*) }
                .ewram2 { *(.ewram2 .ewram2.*) }
                .ewram3 { *(.ewram3 .ewram3.*) }
                .ewram4 { *(.ewram4 .ewram4.*) }
                .ewram5 { *(.ewram5 .ewram5.*) }
                .ewram6 { *(.ewram6 .ewram6.*) }
                .ewram7 { *(.ewram7 .ewram7.*) }
                .ewram8 { *(.ewram8 .ewram8.*) }
                .ewram9 { *(.ewram9 .ewram9.*) }
                .ewramA { *(.ewramA .ewramA.*) }
                .ewramB { *(.ewramB .ewramB.*) }
                .ewramC { *(.ewramC .ewramC.*) }
                .ewramD { *(.ewramD .ewramD.*) }
                .ewramE { *(.ewramE .ewramE.*) }
                .ewramF { *(.ewramF .ewramF.*) }
        } >EWRAM AT>LOAD_REGION

        /* Standard data */

        .data :
        {
                *(.data .data.* .gnu.linkonce.d.*)
        } >DATA_REGION AT>LOAD_REGION

        /* Persistent data */

        .persistent :
        {
                *(.persistent .persistent.* .gnu.linkonce.p.*)
        } >PERSISTENT_REGION AT>LOAD_REGION

        /* IWRAM BSS */

        .iwram.bss (NOLOAD) :
        {
                *(.iwram_bss .iwram_bss.*)
        } >IWRAM

        /* EWRAM BSS */

        .ewram.bss (NOLOAD) :
        {
                *(.ewram_bss .ewram_bss.*)
                /* devkitARM compatibility */
                *(.sbss .sbss.*)
        } >EWRAM

        /* Standard BSS */

        .bss (NOLOAD) :
        {
                *(.bss .bss.* .gnu.linkonce.b.*)
                *(COMMON)
        } >BSS_REGION

        /* Persistent BSS */

        .noinit (NOLOAD) :
        {
                *(.noinit .noinit.* .gnu.linkonce.n.*)
        } >NOINIT_REGION

        /* Empty marker sections for memory regions */

        .load.end : {} >LOAD_REGION

        __load = ORIGIN(LOAD_REGION);
        __load_end = ADDR(.load.end);

        .iwram.end : {} >IWRAM

        __iwram_end = ADDR(.iwram.end);

        .ewram.end : {} >EWRAM

        __ewram_end = ADDR(.ewram.end);

        /* Section symbols */

        __iwram_vma = ADDR(.iwram);
        __iwram_lma = LOADADDR(.iwram);
        __iwram_len = SIZEOF(.iwram);

        __ewram_vma = ADDR(.ewram);
        __ewram_lma = LOADADDR(.ewram);
        __ewram_len = SIZEOF(.ewram);

        __data_vma = ADDR(.data);
        __data_lma = LOADADDR(.data);
        __data_len = SIZEOF(.data);

        __persistent_vma = ADDR(.persistent);
        __persistent_lma = LOADADDR(.persistent);
        __persistent_len = SIZEOF(.persistent);

        __iwram_bss_vma = ADDR(.iwram.bss);
        __iwram_bss_len = SIZEOF(.iwram.bss);

        __ewram_bss_vma = ADDR(.ewram.bss);
        __ewram_bss_len = SIZEOF(.ewram.bss);

        __bss_vma = ADDR(.bss);
        __bss_len = SIZEOF(.bss);

        __noinit_vma = ADDR(.noinit);
        __noinit_len = SIZEOF(.noinit);

        /* libc-compatibility symbols */

        /* Stabs debugging sections.  */
        .stab          0 : { *(.stab) }
        .stabstr       0 : { *(.stabstr) }
        .stab.excl     0 : { *(.stab.excl) }
        .stab.exclstr  0 : { *(.stab.exclstr) }
        .stab.index    0 : { *(.stab.index) }
        .stab.indexstr 0 : { *(.stab.indexstr) }
        .comment       0 : { *(.comment) }
        .gnu.build.attributes : { *(.gnu.build.attributes .gnu.build.attributes.*) }
        /* DWARF debug sections.
           Symbols in the DWARF debugging sections are relative to the beginning
           of the section so we begin them at 0.  */
        /* DWARF 1.  */
        .debug          0 : { *(.debug) }
        .line           0 : { *(.line) }
        /* GNU DWARF 1 extensions.  */
        .debug_srcinfo  0 : { *(.debug_srcinfo) }
        .debug_sfnames  0 : { *(.debug_sfnames) }
        /* DWARF 1.1 and DWARF 2.  */
        .debug_aranges  0 : { *(.debug_aranges) }
        .debug_pubnames 0 : { *(.debug_pubnames) }
        /* DWARF 2.  */
        .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
        .debug_abbrev   0 : { *(.debug_abbrev) }
        .debug_line     0 : { *(.debug_line .debug_line.* .debug_line_end) }
        .debug_frame    0 : { *(.debug_frame) }
        .debug_str      0 : { *(.debug_str) }
        .debug_loc      0 : { *(.debug_loc) }
        .debug_macinfo  0 : { *(.debug_macinfo) }
        /* SGI/MIPS DWARF 2 extensions.  */
        .debug_weaknames 0 : { *(.debug_weaknames) }
        .debug_funcnames 0 : { *(.debug_funcnames) }
        .debug_typenames 0 : { *(.debug_typenames) }
        .debug_varnames  0 : { *(.debug_varnames) }
        /* DWARF 3.  */
        .debug_pubtypes 0 : { *(.debug_pubtypes) }
        .debug_ranges   0 : { *(.debug_ranges) }
        /* DWARF 5.  */
        .debug_addr     0 : { *(.debug_addr) }
        .debug_line_str 0 : { *(.debug_line_str) }
        .debug_loclists 0 : { *(.debug_loclists) }
        .debug_macro    0 : { *(.debug_macro) }
        .debug_names    0 : { *(.debug_names) }
        .debug_rnglists 0 : { *(.debug_rnglists) }
        .debug_str_offsets 0 : { *(.debug_str_offsets) }
        .debug_sup      0 : { *(.debug_sup) }
        .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) KEEP (*(.gnu.attributes)) }
        .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
        .note.gnu.build-id  : { *(.note.gnu.build-id) }
        /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) }
}

/* vim: set et sta sw=8 sts=8: */
