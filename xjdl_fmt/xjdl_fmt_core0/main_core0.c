//#############################################################################
//
// Copyright (C) 2024 STARRYSTONETECH - http://www.starrystonetech.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of STARRYSTONETECH nor the names of its contributors 
//   may be used to endorse or promote products derived from this software 
//   without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//#############################################################################

#include "driverlib.h"
#include "device.h"

#include <rtthread.h>
#include <rtdef.h>

//#include "rt_module_test/rt_timer_test.h"
//#include "rt_module_test/rt_thread_test.h"
//#include "rt_module_test/rt_sem_test.h"
//#include "rt_module_test/rt_mutex_test.h"
//#include "rt_module_test/rt_event_test.h"
//#include "rt_module_test/rt_mailbox_test.h"
//#include "rt_module_test/rt_message_queue_test.h"
//#include "rt_module_test/rt_module_test_macro.h"
//#include "rt_module_test/rt_serial_device_test.h"
//#include "rt_module_test/rt_pin_device_test.h"

rt_uint32_t core0_cnt = 0;

int main(void)
{
    while(1){
        if(++core0_cnt > 0x10000){
            core0_cnt = 0;
        }
    }

    return 0;
}
