/*
 * 2024.04.30 build for qx environment
 */
.extern get_rt_thread_switch_interrupt_flag_addr
.extern get_rt_from_thread_addr
.extern get_rt_to_thread_addr
.extern trigger_rt_thread_intr

/****************************************************************************************************/
.global rt_hw_interrupt_enable
rt_hw_interrupt_enable:
movigh gr2 0x007f||
movigl gr2 0x0700||
||store32 gr4 gr2 8
ret||
nop||
nop||


.global rt_hw_interrupt_disable
rt_hw_interrupt_disable:
movigh gr3 0x007f||
movigl gr3 0x0700||
movigh gr4 0x0||
movigl gr4 0x1||
|load32 gr2 gr3 8|
||store32 gr4 gr3 8
ret||
nop||
nop||

/****************************************************************************************************/

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * GR4 --> to
 */
 .global rt_hw_context_switch_to
rt_hw_context_switch_to:
addi gr30 gr30 0xfffC||
||store32 gr31 gr30 0

call get_rt_to_thread_addr||
nop||
nop||
||store32 gr4 gr2 0x0

call get_rt_from_thread_addr||
nop||
nop||
movigl gr0 0x0||
movigh gr0 0x0||
||store32 gr0 gr2 0x0

call get_rt_thread_switch_interrupt_flag_addr||
nop||
nop||
movigl gr0 0x1||
movigh gr0 0x0||
||store32 gr0 gr2 0x0

movigh gr0 0x007F||
movigl gr0 0x0F08||
|load32 gr1 gr0 0|
bst gr1 8||
||store32 gr1 gr0 0

|load32 gr31 gr30 0|
addi gr30 gr30 4||

movigh gr0 0x007F||
movigl gr0 0x0720||
movigh gr1 0x0||
movigl gr1 0x0||
||store32 gr1 gr0 0x0

/* never reach here! */
fake_loop:
jmp fake_loop||
nop||
nop||


/*******************************************************************************************/
/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * GR4 --> from
 * GR5 --> to
 */
.global rt_hw_context_switch_interrupt
.global rt_hw_context_switch

rt_hw_context_switch_interrupt:
rt_hw_context_switch:
addi gr30 gr30 0xfffC||
||store32 gr31 gr30 0

call get_rt_thread_switch_interrupt_flag_addr||
nop||
nop||
|load32 gr0 gr2 0x0|
eqi gr0 0x1||
jc _reswitch||

movigl gr0 0x1||
movigh gr0 0x0||
||store32 gr0 gr2 0x0

call get_rt_from_thread_addr||
nop||
nop||
||store32 gr4 gr2 0x0

_reswitch:
call get_rt_to_thread_addr||
nop||
nop||
||store32 gr5 gr2 0x0

|load32 gr31 gr30 0|
addi gr30 gr30 4||

movigh gr0 0x007F||
movigl gr0 0x0F08||
|load32 gr1 gr0 0|
bst gr1 8||
||store32 gr1 gr0 0

ret||
nop||
nop||

/*******************************************************************************************/
.global rt_thread_soft_intr_handler
rt_thread_soft_intr_handler:
/* 1.close global intr
 * hardware work,no need for software movement
 */
#movigh gr0 0x007F||
#movigl gr0 0x0720||
#movigh gr1 0x0||
#movigl gr1 0x1||
#||store32 gr1 gr0 0x0

/* 2.disable erad cmt1 */
movigh gr0 0x007F||
movigl gr0 0x0F08||
|load32 gr1 gr0 0|
bclr gr1 8||
||store32 gr1 gr0 0

/* 3.clear erad cmt1 event */
movigh gr0 0x007F||
movigl gr0 0x1818||
|load32 gr1 gr0 0|
bst gr1 0||
||store32 gr1 gr0 0

/* !!!before calling c function, you need store your link reg!!!
 * othervise link reg will be changed by calling c function
 */
addi gr30 gr30 0xff78||
||store32 gr31 gr30 31

/* 4.get need of context switch */
call get_rt_thread_switch_interrupt_flag_addr||
nop||
nop||
|load32 gr0 gr2 0x0|
eqi gr0 0x0||
jc rt_thread_exit||

/* 5.real need of context switch,first clear need flag,then handle */
movigl gr0 0x0||
movigh gr0 0x0||
||store32 gr0 gr2 0x0

/* 6.get from thread sp */
call get_rt_from_thread_addr||
nop||
nop||
|load32 gr0 gr2 0x0|
eqi gr0 0x0||
jc switch_to_thread||

/* 7.save from stack */
# reserve stack space, SP <= SP - 144

#||store32 gr0 gr30 0
#||store32 gr1 gr30 1
||store32 gr2 gr30 2
||store32 gr3 gr30 3
||store32 gr4 gr30 4
||store32 gr5 gr30 5
||store32 gr6 gr30 6
||store32 gr7 gr30 7
||store32 gr8 gr30 8
||store32 gr9 gr30 9
||store32 gr10 gr30 10
||store32 gr11 gr30 11
||store32 gr12 gr30 12
||store32 gr13 gr30 13
||store32 gr14 gr30 14
||store32 gr15 gr30 15
||store32 gr16 gr30 16
||store32 gr17 gr30 17
||store32 gr18 gr30 18
||store32 gr19 gr30 19
||store32 gr20 gr30 20
||store32 gr21 gr30 21
||store32 gr22 gr30 22
||store32 gr23 gr30 23
||store32 gr24 gr30 24
||store32 gr25 gr30 25
||store32 gr26 gr30 26
||store32 gr27 gr30 27
||store32 gr28 gr30 28
||store32 gr29 gr30 29
||store32 gr30 gr30 30


movc2g gr1||
||store32 gr1 gr30 32

movigh gr1 0x007F||
movigl gr1 0x0718||
|load32 gr2 gr1 0x0|
||store32 gr2 gr30 33

/* 8.save sp to gloable from */
||store32 gr30 gr0 0

switch_to_thread:
call get_rt_to_thread_addr||
nop||
nop||
|load32 gr0 gr2 0x0|
|load32 gr30 gr0 0x0|

movigh gr1 0x007F||
movigl gr1 0x0718||
|load32 gr2 gr30 33|
||store32 gr2 gr1 0

|load32 gr2 gr30 32|
movg2c gr2||

|load32 gr31 gr30 31|
|load32 gr29 gr30 29|
|load32 gr28 gr30 28|
|load32 gr27 gr30 27|
|load32 gr26 gr30 26|
|load32 gr25 gr30 25|
|load32 gr24 gr30 24|
|load32 gr23 gr30 23|
|load32 gr22 gr30 22|
|load32 gr21 gr30 21|
|load32 gr20 gr30 20|
|load32 gr19 gr30 19|
|load32 gr18 gr30 18|
|load32 gr17 gr30 17|
|load32 gr16 gr30 16|
|load32 gr15 gr30 15|
|load32 gr14 gr30 14|
|load32 gr13 gr30 13|
|load32 gr12 gr30 12|
|load32 gr11 gr30 11|
|load32 gr10 gr30 10|
|load32 gr9  gr30  9|
|load32 gr8  gr30  8|
|load32 gr7  gr30  7|
|load32 gr6  gr30  6|
|load32 gr5  gr30  5|
|load32 gr4  gr30  4|
|load32 gr3  gr30  3|
|load32 gr2  gr30  2|
#|load32 gr1  gr30  1|
#|load32 gr0  gr30  0|

addi gr30 gr30 136||

rt_thread_exit:
/*
 * hardware done in rtt step
 * no need for software movement
 */
#movigh gr0 0x007F||
#movigl gr0 0x0720||
#movigh gr1 0x0||
#movigl gr1 0x0||
#||store32 gr1 gr0 0x0

rtt||
nop||
nop||
