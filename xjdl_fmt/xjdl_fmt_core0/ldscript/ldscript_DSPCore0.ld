OUTPUT_FORMAT("elf32-tradlittlemips", "elf32-tradbigmips", "elf32-tradlittlemips")

ENTRY(_dsp_start)

INCLUDE "ldscript_Memory.ld"

SECTIONS
{
  __data_start__ = ORIGIN(GSD_RAM_RESERVED);
  . = __data_start__;
  .fill   : { LONG(0xDEADBEEF)        } > GSD_RAM_RESERVED
  .rodata : { 
  *(.rodata) 
  *(.rodata.*) 
  . = ALIGN(0x10); 

    /* section information for finsh shell */
    . = ALIGN(4);
    __fsymtab_start = .;
    KEEP(*(FSymTab))
    __fsymtab_end = .;
    . = ALIGN(4);
    __vsymtab_start = .;
    KEEP(*(VSymTab))
    __vsymtab_end = .;
    . = ALIGN(4);
 
    /* section information for initial. */
    . = ALIGN(4);
    __rt_init_start = .;
    KEEP(*(SORT(.rti_fn*)))
    __rt_init_end = .;
    . = ALIGN(4);

    /* section information for modules */
    . = ALIGN(4);
    __rtmsymtab_start = .;
    KEEP(*(RTMSymTab))
    __rtmsymtab_end = .;
    
  } > GSD_RAM_CORE0

  .data   : { *(.data)   *(.data.*)  . = ALIGN(0x10);  } > GSD_RAM_CORE0
  .sdata  : { *(.sdata)  *(.sdata.*) . = ALIGN(0x10);  } > GSD_RAM_CORE0
  __bss_start = .;
  .sbss   : { *(.sbss) *(.sbss.*) *(.scommon) . = ALIGN(0x10);  } > GSD_RAM_CORE0
  .bss    : { *(.bss)  *(.bss.*)  *(COMMON)   . = ALIGN(0x10); } > GSD_RAM_CORE0
  __data_end__ = .;

  /* for fake bootloader when debugging on RAM */
  .text.qxbootdebug : { KEEP(*(.text.qxbootdebug)) } > BOOT_RAM

  __text_start__ = ORIGIN(GSI_RAM_CORE0);
  . = __text_start__;
  .text : {
    KEEP(*(.text.interrupt.vector))
    *(.text)
    *(.text.*)
    . = ALIGN(0x10);
  } > GSI_RAM_CORE0 =0x00000080
  __text_end__ = .;

  PROVIDE(_DSP_STACK_TOP = ORIGIN(GSD_RAM_CORE0) + LENGTH(GSD_RAM_CORE0));
  /* must use lower case letter below to fit linker */
  PROVIDE(_dsp_stack_top_hi = ((_DSP_STACK_TOP >> 16) & 0xFFFF));
  PROVIDE(_dsp_stack_top_lo = ((_DSP_STACK_TOP >>  0) & 0xFFFF));

  PROVIDE(_CORE0_IRAM_START = ORIGIN(GSI_RAM_CORE0));
  PROVIDE(_CORE1_IRAM_START = ORIGIN(GSI_RAM_CORE0));

  PROVIDE(_dsp_bss_start_hi = ((__bss_start  >> 16) & 0xFFFF));
  PROVIDE(_dsp_bss_start_lo = ((__bss_start  >>  0) & 0xFFFF));
  PROVIDE(_dsp_data_end_hi  = ((__data_end__ >> 16) & 0xFFFF));
  PROVIDE(_dsp_data_end_lo  = ((__data_end__ >>  0) & 0xFFFF));

  PROVIDE(__end = __data_end__);
  PROVIDE(__stack_end = ORIGIN(GSD_RAM_CORE0) + LENGTH(GSD_RAM_CORE0) - LENGTH(STACK_CORE0));
}

INCLUDE "ldscript_Peripheral.ld"
INCLUDE "ldscript_DebugInfo.ld"
