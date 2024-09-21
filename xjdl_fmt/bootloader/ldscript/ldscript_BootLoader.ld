OUTPUT_FORMAT("elf32-tradlittlemips", "elf32-tradbigmips", "elf32-tradlittlemips")

ENTRY(_dsp_boot_start)

INCLUDE "ldscript_Memory.ld"

SECTIONS
{
  __text_start__ = ORIGIN(BOOT_RAM);
  .text : {
    *(.text.qxboot)
    *(.text)
    *(.text.*)
    . = ALIGN(0x10);
  } > BOOT_RAM =0x00000080
  __text_end__ = .;

  /* to mask off the 0x4 from GSD_RAM_RESERVED */
  PROVIDE(_DRAM_START_MASK_ = 0xFFFFFFF8);
  PROVIDE(_CORE0_DRAM_START = ORIGIN(GSD_RAM_CORE0) & _DRAM_START_MASK_);
  PROVIDE(_CORE1_DRAM_START = ORIGIN(GSD_RAM_CORE1) & _DRAM_START_MASK_);
  PROVIDE(_CORE0_IRAM_START = ORIGIN(GSI_RAM_CORE0));
  PROVIDE(_CORE1_IRAM_START = ORIGIN(GSI_RAM_CORE1));

  PROVIDE(_CORE0_CODE_ENTRY = ORIGIN(GSI_RAM_CORE0) + 0x400);
  
  PROVIDE(_BOOT_LOADER_SP = ORIGIN(GSD_RAM_CORE0) + LENGTH(GSD_RAM_CORE0));
  /* must use lower case letter below to fit linker */
  PROVIDE(_boot_loader_sp_hi = ((_BOOT_LOADER_SP >> 16) & 0xFFFF));
  PROVIDE(_boot_loader_sp_lo = ((_BOOT_LOADER_SP >>  0) & 0xFFFF));

  /* bootloader currently is not allowed to have data sections */
  /DISCARD/ : { *(.data)  }
  /DISCARD/ : { *(.bss)   }
  /DISCARD/ : { *(COMMON) }
}

INCLUDE "ldscript_Peripheral.ld"
INCLUDE "ldscript_DebugInfo.ld"
