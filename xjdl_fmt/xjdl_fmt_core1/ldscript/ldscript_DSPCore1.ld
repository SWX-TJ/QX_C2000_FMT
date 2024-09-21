OUTPUT_FORMAT("elf32-tradlittlemips", "elf32-tradbigmips", "elf32-tradlittlemips")

ENTRY(_dsp_start)

INCLUDE "ldscript_Memory.ld"

SECTIONS
{
  __data_start__ = ORIGIN(GSD_RAM_CORE1);
  . = __data_start__;
  .rodata : { *(.rodata) *(.rodata.*) } > GSD_RAM_CORE1
  .data   : { *(.data)   *(.data.*)   } > GSD_RAM_CORE1
  .sdata  : { *(.sdata)  *(.sdata.*)  } > GSD_RAM_CORE1
  __bss_start = .;
  .sbss   : { *(.sbss) *(.sbss.*) *(.scommon) } > GSD_RAM_CORE1
  .bss    : { *(.bss)  *(.bss.*)  *(COMMON)   } > GSD_RAM_CORE1
  __data_end__ = .;

  __text_start__ = ORIGIN(GSI_RAM_CORE1);
  . = __text_start__;
  .text : {
    KEEP(*(.text.interrupt.vector))
    KEEP(*(.text.interrupt.routine))
    *(.text)
    *(.text.*)
    . = ALIGN(0x10);
  } > GSI_RAM_CORE1 =0x00000080
  __text_end__ = .;

  /* discard unnecessary fake bootloader for core1 */
  /DISCARD/ : { *(.text.qxbootdebug) }

  PROVIDE(_DSP_STACK_TOP = ORIGIN(GSD_RAM_CORE1) + LENGTH(GSD_RAM_CORE1));
  /* must use lower case letter below to fit linker */
  PROVIDE(_dsp_stack_top_hi = ((_DSP_STACK_TOP >> 16) & 0xFFFF));
  PROVIDE(_dsp_stack_top_lo = ((_DSP_STACK_TOP >>  0) & 0xFFFF));

  PROVIDE(_dsp_bss_start_hi = ((__bss_start  >> 16) & 0xFFFF));
  PROVIDE(_dsp_bss_start_lo = ((__bss_start  >>  0) & 0xFFFF));
  PROVIDE(_dsp_data_end_hi  = ((__data_end__ >> 16) & 0xFFFF));
  PROVIDE(_dsp_data_end_lo  = ((__data_end__ >>  0) & 0xFFFF));

  PROVIDE(__end = __data_end__);
  PROVIDE(__stack_end = ORIGIN(GSD_RAM_CORE1) + LENGTH(GSD_RAM_CORE1) - LENGTH(STACK_CORE1));
}

INCLUDE "ldscript_Peripheral.ld"
INCLUDE "ldscript_DebugInfo.ld"
