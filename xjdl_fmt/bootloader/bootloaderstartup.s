.global _dsp_boot_start
.global _dsp_boot_jmp_to_core0
.extern qx_bootloader_main

.section .text.qxboot
_dsp_boot_start:
movigh GR30 _boot_loader_sp_hi||
movigl GR30 _boot_loader_sp_lo||
jmp qx_bootloader_main||
nop||
nop||

_dsp_boot_jmp_to_core0:
jmpr GR4||
nop||
nop||
