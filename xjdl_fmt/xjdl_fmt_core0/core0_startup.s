# export _dsp_start for link script
.global _dsp_start

# declare symbol main for C function main()
.extern main

.section .text.interrupt.vector
jmp exception_nc||
movigl GR28 0xBF00||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF01||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF02||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF03||
nop||
nop||

jmp pic_group_nc||
movigl GR28 0xBF04||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF05||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF6||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF07||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF08||
nop||
nop||

jmp pic_group_nc||
movigl GR28 0xBF09||
nop||
nop||

#0 10
nop||
nop||
nop||
nop||

#0 11
nop||
nop||
nop||
nop||

#0 12
nop||
nop||
nop||
nop||

#0 13
nop||
nop||
nop||
nop||

#0 14
nop||
nop||
nop||
nop||

#0 15
nop||
nop||
nop||
nop||

#1 0
jmp rt_thread_soft_intr_handler||
nop||
nop||
nop||

#1 1
jmp trace_isr||
nop||
nop||
nop||

#1 2
jmp wp_isr||
nop||
nop||
nop||

#1 3
jmp adca1_isr||
nop||
nop||
nop||

#1 4
jmp adcb1_isr||
nop||
nop||
nop||

#1 5
jmp adcc1_isr||
nop||
nop||
nop||

#1 6
jmp xint1_isr||
nop||
nop||
nop||

#1 7
jmp xint2_isr||
nop||
nop||
nop||

#1 8
nop||
nop||
nop||
nop||

#1 9
jmp rt_thread_tick_intr||
nop||
nop||
nop||

#1 10
jmp wake_wdog_isr||
nop||
nop||
nop||

#1 11
nop||
nop||
nop||
nop||

#1 12
nop||
nop||
nop||
nop||

#1 13
jmp adca_hr1_isr||
nop||
nop||
nop||

#1 14
jmp adcb_hr1_isr||
nop||
nop||
nop||

#1 15
jmp adcc_hr1_isr||
nop||
nop||
nop||

#2 0
jmp epwm1_tz_isr||
nop||
nop||
nop||

#2 1
jmp epwm2_tz_isr||
nop||
nop||
nop||

#2 2
jmp epwm3_tz_isr||
nop||
nop||
nop||

#2 3
jmp epwm4_tz_isr||
nop||
nop||
nop||

#2 4
jmp epwm5_tz_isr||
nop||
nop||
nop||

#2 5
jmp epwm6_tz_isr||
nop||
nop||
nop||

#2 6
jmp epwm7_tz_isr||
nop||
nop||
nop||

#2 7
jmp epwm8_tz_isr||
nop||
nop||
nop||

#2 8
jmp epwm9_tz_isr||
nop||
nop||
nop||

#2 9
jmp epwm10_tz_isr||
nop||
nop||
nop||

#2 10
jmp epwm11_tz_isr||
nop||
nop||
nop||

#2 11
jmp epwm12_tz_isr||
nop||
nop||
nop||

#2 12
nop||
nop||
nop||
nop||

#2 13
nop||
nop||
nop||
nop||

#2 14
nop||
nop||
nop||
nop||

#2 15
nop||
nop||
nop||
nop||

#3 0
jmp epwm1_isr||
nop||
nop||
nop||

#3 1
jmp epwm2_isr||
nop||
nop||
nop||

#3 2
jmp epwm3_isr||
nop||
nop||
nop||

#3 3
jmp epwm4_isr||
nop||
nop||
nop||

#3 4
jmp epwm5_isr||
nop||
nop||
nop||

#3 5
jmp epwm6_isr||
nop||
nop||
nop||

#3 6
jmp epwm7_isr||
nop||
nop||
nop||

#3 7
jmp epwm8_isr||
nop||
nop||
nop||

#3 8
jmp epwm9_isr||
nop||
nop||
nop||

#3 9
jmp epwm10_isr||
nop||
nop||
nop||

#3 10
jmp epwm11_isr||
nop||
nop||
nop||

#3 11
jmp epwm12_isr||
nop||
nop||
nop||

#3 12
nop||
nop||
nop||
nop||

#3 13
nop||
nop||
nop||
nop||

#3 14
nop||
nop||
nop||
nop||

#3 15
nop||
nop||
nop||
nop||

#nc 0 reset
_dsp_start:
jmp _dsp_call_main||
nop||
nop||
nop||

#nc 1
nop||
nop||
nop||
nop||

#nc 2
nop||
nop||
nop||
nop||

#nc 3
nop||
nop||
nop||
nop||

#nc 4
nop||
nop||
nop||
nop||

#nc 5
nop||
nop||
nop||
nop||

#nc 6
nop||
nop||
nop||
nop||

#nc 7
nop||
nop||
nop||
nop||

#nc 8
nop||
nop||
nop||
nop||

#nc 9
nop||
nop||
nop||
nop||

#nc 10
nop||
nop||
nop||
nop||

#nc 11
nop||
nop||
nop||
nop||

#nc 12
nop||
nop||
nop||
nop||

#nc 13
nop||
nop||
nop||
nop||

#nc 14
nop||
nop||
nop||
nop||

#nc 15
nop||
nop||
nop||
nop||

#4 0
jmp ecap1_isr||
nop||
nop||
nop||

#4 1
jmp ecap2_isr||
nop||
nop||
nop||

#4 2
jmp ecap3_isr||
nop||
nop||
nop||

#4 3
jmp ecap4_isr||
nop||
nop||
nop||

#4 4
jmp ecap5_isr||
nop||
nop||
nop||

#4 5
jmp ecap6_isr||
nop||
nop||
nop||

#4 6
jmp ecap7_isr||
nop||
nop||
nop||

#4 7
nop||
nop||
nop||
nop||

#4 8
nop||
nop||
nop||
nop||

#4 9
nop||
nop||
nop||
nop||

#4 10
nop||
nop||
nop||
nop||

#4 11
nop||
nop||
nop||
nop||

#4 12
nop||
nop||
nop||
nop||

#4 13
jmp ecap6_hrcal_isr||
nop||
nop||
nop||

#4 14
jmp ecap7_hrcal_isr||
nop||
nop||
nop||

#4 15
nop||
nop||
nop||
nop||

#5 0
jmp eqep1_isr||
nop||
nop||
nop||

#5 1
jmp eqep2_isr||
nop||
nop||
nop||

#5 2
nop||
nop||
nop||
nop||

#5 3
nop||
nop||
nop||
nop||

#5 4
nop||
nop||
nop||
nop||

#5 5
nop||
nop||
nop||
nop||

#5 6
nop||
nop||
nop||
nop||

#5 7
nop||
nop||
nop||
nop||

#5 8
jmp sdfm1_isr||
nop||
nop||
nop||

#5 9
nop||
nop||
nop||
nop||

#5 10
nop||
nop||
nop||
nop||

#5 11
nop||
nop||
nop||
nop||

#5 12
jmp sdfm1dr1_isr||
nop||
nop||
nop||

#5 13
jmp sdfm1dr2_isr||
nop||
nop||
nop||

#5 14
jmp sdfm1dr3_isr||
nop||
nop||
nop||

#5 15
jmp sdfm1dr4_isr||
nop||
nop||
nop||

#6 0
jmp spia_m_isr||
nop||
nop||
nop||

#6 1
jmp spia_s_isr||
nop||
nop||
nop||

#6 2
jmp spib_m_isr||
nop||
nop||
nop||

#6 3
jmp spib_s_isr||
nop||
nop||
nop||

#6 4
jmp spic_m_isr||
nop||
nop||
nop||

#6 5
jmp spic_s_isr||
nop||
nop||
nop||

#6 6
jmp spid_m_isr||
nop||
nop||
nop||

#6 7
jmp spid_s_isr||
nop||
nop||
nop||

#6 8
nop||
nop||
nop||
nop||

#6 9
nop||
nop||
nop||
nop||

#6 10
nop||
nop||
nop||
nop||

#6 11
nop||
nop||
nop||
nop||

#6 12
nop||
nop||
nop||
nop||

#6 13
nop||
nop||
nop||
nop||

#6 14
nop||
nop||
nop||
nop||

#6 15
nop||
nop||
nop||
nop||

#7 0
jmp dma_ch1_isr||
nop||
nop||
nop||

#7 1
jmp dma_ch2_isr||
nop||
nop||
nop||

#7 2
jmp dma_ch3_isr||
nop||
nop||
nop||

#7 3
jmp dma_ch4_isr||
nop||
nop||
nop||

#7 4
jmp dma_ch5_isr||
nop||
nop||
nop||

#7 5
jmp dma_ch6_isr||
nop||
nop||
nop||

#7 6
nop||
nop||
nop||
nop||

#7 7
nop||
nop||
nop||
nop||

#7 8
nop||
nop||
nop||
nop||

#7 9
nop||
nop||
nop||
nop||

#7 10
jmp fsitx_int1_isr||
nop||
nop||
nop||

#7 11
jmp fsitx_int2_isr||
nop||
nop||
nop||

#7 12
jmp fsirx_int1_isr||
nop||
nop||
nop||

#7 13
jmp fsirx_int2_isr||
nop||
nop||
nop||

#7 14
nop||
nop||
nop||
nop||

#7 15
jmp dcc_isr||
nop||
nop||
nop||

#8 0
jmp i2ca_isr||
nop||
nop||
nop||

#8 1
nop||
nop||
nop||
nop||

#8 2
nop||
nop||
nop||
nop||

#8 3
nop||
nop||
nop||
nop||

#8 4
nop||
nop||
nop||
nop||

#8 5
nop||
nop||
nop||
nop||

#8 6
nop||
nop||
nop||
nop||

#8 7
nop||
nop||
nop||
nop||

#8 8
jmp lina_isr||
nop||
nop||
nop||

#8 9
nop||
nop||
nop||
nop||

#8 10
nop||
nop||
nop||
nop||

#8 11
nop||
nop||
nop||
nop||

#8 12
jmp pmbus_isr||
nop||
nop||
nop||

#8 13
nop||
nop||
nop||
nop||

#8 14
nop||
nop||
nop||
nop||

#8 15
nop||
nop||
nop||
nop||

#9 0
jmp scia_isr||
nop||
nop||
nop||

#9 1
jmp scib_isr||
nop||
nop||
nop||

#9 2
jmp scic_isr||
nop||
nop||
nop||

#9 3
jmp scid_isr||
nop||
nop||
nop||

#9 4
jmp cana_isr||
nop||
nop||
nop||

#9 5
jmp canb_isr||
nop||
nop||
nop||

#9 6
nop||
nop||
nop||
nop||

#9 7
nop||
nop||
nop||
nop||

#9 8
nop||
nop||
nop||
nop||

#9 9
nop||
nop||
nop||
nop||

#9 10
nop||
nop||
nop||
nop||

#9 11
nop||
nop||
nop||
nop||

#9 12
nop||
nop||
nop||
nop||

#9 13
nop||
nop||
nop||
nop||

#9 14
nop||
nop||
nop||
nop||

#9 15
nop||
nop||
nop||
nop||

#10 0
jmp adca_evt_isr||
nop||
nop||
nop||

#10 1
jmp adca2_isr||
nop||
nop||
nop||

#10 2
jmp adca3_isr||
nop||
nop||
nop||

#10 3
jmp adca4_isr||
nop||
nop||
nop||

#10 4
jmp adcb_evt_isr||
nop||
nop||
nop||

#10 5
jmp adcb2_isr||
nop||
nop||
nop||

#10 6
jmp adcb3_isr||
nop||
nop||
nop||

#10 7
jmp adcb4_isr||
nop||
nop||
nop||

#10 8
jmp adcc_evt_isr||
nop||
nop||
nop||

#10 9
jmp adcc2_isr||
nop||
nop||
nop||

#10 10
jmp adcc3_isr||
nop||
nop||
nop||

#10 11
jmp adcc4_isr||
nop||
nop||
nop||

#10 12
jmp adca_hs_isr||
nop||
nop||
nop||

#10 13
jmp adcb_hs_isr||
nop||
nop||
nop||

#10 14
jmp adcc_hs_isr||
nop||
nop||
nop||

#10 15
nop||
nop||
nop||
nop||

#11 0
jmp ipc_0_isr||
nop||
nop||
nop||

#11 1
jmp ipc_1_isr||
nop||
nop||
nop||

#11 2
jmp ipc_2_isr||
nop||
nop||
nop||

#11 3
jmp ipc_3_isr||
nop||
nop||
nop||

#11 4
nop||
nop||
nop||
nop||

#11 5
nop||
nop||
nop||
nop||

#11 6
nop||
nop||
nop||
nop||

#11 7
nop||
nop||
nop||
nop||

#11 8
nop||
nop||
nop||
nop||

#11 9
nop||
nop||
nop||
nop||

#11 10
nop||
nop||
nop||
nop||

#11 11
nop||
nop||
nop||
nop||

#11 12
nop||
nop||
nop||
nop||

#11 13
nop||
nop||
nop||
nop||

#11 14
nop||
nop||
nop||
nop||

#11 15
nop||
nop||
nop||
nop||

#12 0
jmp xint3_isr||
nop||
nop||
nop||

#12 1
jmp xint4_isr||
nop||
nop||
nop||

#12 2
jmp xint5_isr||
nop||
nop||
nop||

#12 3
jmp xintf_isr||
movigl GR28 0xBFF1||
nop||
nop||
nop||

#12 4
jmp adca_hr_evt_isr||
nop||
nop||
nop||

#12 5
jmp adca_hr2_isr||
nop||
nop||
nop||

#12 6
jmp adca_hr3_isr||
nop||
nop||
nop||

#12 7
jmp adca_hr4_isr||
nop||
nop||
nop||

#12 8
jmp adcb_hr_evt_isr||
nop||
nop||
nop||

#12 9
jmp adcb_hr2_isr||
nop||
nop||
nop||

#12 10
jmp adcb_hr3_isr||
nop||
nop||
nop||

#12 11
jmp adcb_hr4_isr||
nop||
nop||
nop||

#12 12
jmp adcc_hr_evt_isr||
nop||
nop||
nop||

#12 13
jmp adcc_hr2_isr||
nop||
nop||
nop||

#12 14
jmp adcc_hr3_isr||
nop||
nop||
nop||

#12 15
jmp adcc_hr4_isr||
nop||
nop||
nop||

#13
jmp timer1_isr||
nop||
nop||
nop||

#14
jmp timer2_isr||
nop||
nop||
nop||

#15
jmp nmi_isr||
nop||
nop||
nop||


_lb_func_init_bss:
# gr2 <= bss_start
movigh gr2 _dsp_bss_start_hi||
movigl gr2 _dsp_bss_start_lo||
# gr3 <= data_end
movigh gr3 _dsp_data_end_hi||
movigl gr3 _dsp_data_end_lo||
# gr4 <= constant 0
movigh gr4 0x0||
movigl gr4 0x0||
_lb_assign_0_loop:
eq gr2 gr3||
jc _lb_func_init_bss_end||
nop||
nop||
||store8 gr4 gr2 0
addi gr2 gr2 1||
jmp _lb_assign_0_loop||
nop||
nop||
_lb_func_init_bss_end:
ret||
nop||
nop||

_dsp_call_main:
# set .bss data section to all zero
call _lb_func_init_bss||
nop||
nop||
# set SP and call main()
movigh GR30 _dsp_stack_top_hi||
movigl GR30 _dsp_stack_top_lo||
call entry||
nop||
nop||

_main_exit_stay_nop:
jmp _main_exit_stay_nop||
nop||
nop||
nop||

_qx_default_isr:
jmp _qx_default_isr||
nop||
nop||
nop||

# declare default ISR for various interrupts
# they have weak linkage type and will be overwritten by corresponding external-linkage ISR defined in C
.weak exception_nc
.weak pic_group_nc
.weak rtos_isr
.weak trace_isr
.weak wp_isr
.weak adca1_isr
.weak adcb1_isr
.weak adcc1_isr
.weak xint1_isr
.weak xint2_isr
.weak timer0_isr
.weak wake_wdog_isr
.weak adca_hr1_isr
.weak adcb_hr1_isr
.weak adcc_hr1_isr
.weak epwm1_tz_isr
.weak epwm2_tz_isr
.weak epwm3_tz_isr
.weak epwm4_tz_isr
.weak epwm5_tz_isr
.weak epwm6_tz_isr
.weak epwm7_tz_isr
.weak epwm8_tz_isr
.weak epwm9_tz_isr
.weak epwm10_tz_isr
.weak epwm11_tz_isr
.weak epwm12_tz_isr
.weak epwm1_isr
.weak epwm2_isr
.weak epwm3_isr
.weak epwm4_isr
.weak epwm5_isr
.weak epwm6_isr
.weak epwm7_isr
.weak epwm8_isr
.weak epwm9_isr
.weak epwm10_isr
.weak epwm11_isr
.weak epwm12_isr
.weak ecap1_isr
.weak ecap2_isr
.weak ecap3_isr
.weak ecap4_isr
.weak ecap5_isr
.weak ecap6_isr
.weak ecap7_isr
.weak ecap6_hrcal_isr
.weak ecap7_hrcal_isr
.weak eqep1_isr
.weak eqep2_isr
.weak sdfm1_isr
.weak sdfm1dr1_isr
.weak sdfm1dr2_isr
.weak sdfm1dr3_isr
.weak sdfm1dr4_isr
.weak spia_m_isr
.weak spia_s_isr
.weak spib_m_isr
.weak spib_s_isr
.weak spic_m_isr
.weak spic_s_isr
.weak spid_m_isr
.weak spid_s_isr
.weak dma_ch1_isr
.weak dma_ch2_isr
.weak dma_ch3_isr
.weak dma_ch4_isr
.weak dma_ch5_isr
.weak dma_ch6_isr
.weak fsitx_int1_isr
.weak fsitx_int2_isr
.weak fsirx_int1_isr
.weak fsirx_int2_isr
.weak dcc_isr
.weak i2ca_isr
.weak lina_isr
.weak pmbus_isr
.weak scia_isr
.weak scib_isr
.weak scic_isr
.weak scid_isr
.weak cana_isr
.weak canb_isr
.weak adca_evt_isr
.weak adca2_isr
.weak adca3_isr
.weak adca4_isr
.weak adcb_evt_isr
.weak adcb2_isr
.weak adcb3_isr
.weak adcb4_isr
.weak adcc_evt_isr
.weak adcc2_isr
.weak adcc3_isr
.weak adcc4_isr
.weak adca_hs_isr
.weak adcb_hs_isr
.weak adcc_hs_isr
.weak ipc_0_isr
.weak ipc_1_isr
.weak ipc_2_isr
.weak ipc_3_isr
.weak xint3_isr
.weak xint4_isr
.weak xint5_isr
.weak xintf_isr
.weak adca_hr_evt_isr
.weak adca_hr2_isr
.weak adca_hr3_isr
.weak adca_hr4_isr
.weak adcb_hr_evt_isr
.weak adcb_hr2_isr
.weak adcb_hr3_isr
.weak adcb_hr4_isr
.weak adcc_hr_evt_isr
.weak adcc_hr2_isr
.weak adcc_hr3_isr
.weak adcc_hr4_isr
.weak timer1_isr
.weak timer2_isr
.weak nmi_isr
.weak _qx_default_isr

exception_nc      = _qx_default_isr
pic_group_nc      = _qx_default_isr
rtos_isr          = _qx_default_isr
trace_isr         = _qx_default_isr
wp_isr            = _qx_default_isr
adca1_isr         = _qx_default_isr
adcb1_isr         = _qx_default_isr
adcc1_isr         = _qx_default_isr
xint1_isr         = _qx_default_isr
xint2_isr         = _qx_default_isr
timer0_isr        = _qx_default_isr
wake_wdog_isr     = _qx_default_isr
adca_hr1_isr      = _qx_default_isr
adcb_hr1_isr      = _qx_default_isr
adcc_hr1_isr      = _qx_default_isr
epwm1_tz_isr      = _qx_default_isr
epwm2_tz_isr      = _qx_default_isr
epwm3_tz_isr      = _qx_default_isr
epwm4_tz_isr      = _qx_default_isr
epwm5_tz_isr      = _qx_default_isr
epwm6_tz_isr      = _qx_default_isr
epwm7_tz_isr      = _qx_default_isr
epwm8_tz_isr      = _qx_default_isr
epwm9_tz_isr      = _qx_default_isr
epwm10_tz_isr     = _qx_default_isr
epwm11_tz_isr     = _qx_default_isr
epwm12_tz_isr     = _qx_default_isr
epwm1_isr         = _qx_default_isr
epwm2_isr         = _qx_default_isr
epwm3_isr         = _qx_default_isr
epwm4_isr         = _qx_default_isr
epwm5_isr         = _qx_default_isr
epwm6_isr         = _qx_default_isr
epwm7_isr         = _qx_default_isr
epwm8_isr         = _qx_default_isr
epwm9_isr         = _qx_default_isr
epwm10_isr        = _qx_default_isr
epwm11_isr        = _qx_default_isr
epwm12_isr        = _qx_default_isr
ecap1_isr         = _qx_default_isr
ecap2_isr         = _qx_default_isr
ecap3_isr         = _qx_default_isr
ecap4_isr         = _qx_default_isr
ecap5_isr         = _qx_default_isr
ecap6_isr         = _qx_default_isr
ecap7_isr         = _qx_default_isr
ecap6_hrcal_isr   = _qx_default_isr
ecap7_hrcal_isr   = _qx_default_isr
eqep1_isr         = _qx_default_isr
eqep2_isr         = _qx_default_isr
sdfm1_isr         = _qx_default_isr
sdfm1dr1_isr      = _qx_default_isr
sdfm1dr2_isr      = _qx_default_isr
sdfm1dr3_isr      = _qx_default_isr
sdfm1dr4_isr      = _qx_default_isr
spia_m_isr        = _qx_default_isr
spia_s_isr        = _qx_default_isr
spib_m_isr        = _qx_default_isr
spib_s_isr        = _qx_default_isr
spic_m_isr        = _qx_default_isr
spic_s_isr        = _qx_default_isr
spid_m_isr        = _qx_default_isr
spid_s_isr        = _qx_default_isr
dma_ch1_isr       = _qx_default_isr
dma_ch2_isr       = _qx_default_isr
dma_ch3_isr       = _qx_default_isr
dma_ch4_isr       = _qx_default_isr
dma_ch5_isr       = _qx_default_isr
dma_ch6_isr       = _qx_default_isr
fsitx_int1_isr    = _qx_default_isr
fsitx_int2_isr    = _qx_default_isr
fsirx_int1_isr    = _qx_default_isr
fsirx_int2_isr    = _qx_default_isr
dcc_isr           = _qx_default_isr
i2ca_isr          = _qx_default_isr
lina_isr          = _qx_default_isr
pmbus_isr         = _qx_default_isr
scia_isr          = _qx_default_isr
scib_isr          = _qx_default_isr
scic_isr          = _qx_default_isr
scid_isr          = _qx_default_isr
cana_isr          = _qx_default_isr
canb_isr          = _qx_default_isr
adca_evt_isr      = _qx_default_isr
adca2_isr         = _qx_default_isr
adca3_isr         = _qx_default_isr
adca4_isr         = _qx_default_isr
adcb_evt_isr      = _qx_default_isr
adcb2_isr         = _qx_default_isr
adcb3_isr         = _qx_default_isr
adcb4_isr         = _qx_default_isr
adcc_evt_isr      = _qx_default_isr
adcc2_isr         = _qx_default_isr
adcc3_isr         = _qx_default_isr
adcc4_isr         = _qx_default_isr
adca_hs_isr       = _qx_default_isr
adcb_hs_isr       = _qx_default_isr
adcc_hs_isr       = _qx_default_isr
ipc_0_isr         = _qx_default_isr
ipc_1_isr         = _qx_default_isr
ipc_2_isr         = _qx_default_isr
ipc_3_isr         = _qx_default_isr
xint3_isr         = _qx_default_isr
xint4_isr         = _qx_default_isr
xint5_isr         = _qx_default_isr
xintf_isr         = _qx_default_isr
adca_hr_evt_isr   = _qx_default_isr
adca_hr2_isr      = _qx_default_isr
adca_hr3_isr      = _qx_default_isr
adca_hr4_isr      = _qx_default_isr
adcb_hr_evt_isr   = _qx_default_isr
adcb_hr2_isr      = _qx_default_isr
adcb_hr3_isr      = _qx_default_isr
adcb_hr4_isr      = _qx_default_isr
adcc_hr_evt_isr   = _qx_default_isr
adcc_hr2_isr      = _qx_default_isr
adcc_hr3_isr      = _qx_default_isr
adcc_hr4_isr      = _qx_default_isr
timer1_isr        = _qx_default_isr
timer2_isr        = _qx_default_isr
nmi_isr           = _qx_default_isr

.section .text
.global qx_precise_delay
# gr4 is the loop count from caller
qx_precise_delay:
addi gr4 gr4 0xffffffff||
nop||
nop||
lei gr4 0||
jnc qx_precise_delay||
nop||
nop||
ret||
nop||
nop||

# fake bootloader for debugging on RAM
.section .text.qxbootdebug
# enable NMI
movigh gr3 0x100||
movigl gr3 0x1200||
|load32 gr4 gr3 0|
bst gr4 0||
||store32 gr4 gr3 0
jmp _dsp_start||
nop||
nop||
nop||
