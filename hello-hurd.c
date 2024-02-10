#define ino64_t __ino64_t

#include <mach/mach_traps.h>
#include <mach/task_special_ports.h>
#include "mach.h"
#include "process.h"
#include "exec_startup.h"
#include "io.h"

void _start() {
    mach_port_t bootstrap;
    vm_address_t user_entry, phdr_data, stack_base;
    vm_size_t phdr_size, stack_size;
    int flags;
    data_t argv, envp;
    mach_msg_type_number_t argvCnt, envpCnt, dtableCnt, portarrayCnt, intarrayCnt;
    portarray_t dtable, portarray;
    intarray_t intarray;

    task_get_special_port(mach_task_self(), TASK_BOOTSTRAP_PORT, &bootstrap);

    exec_startup_get_info(bootstrap, 
        &user_entry,
        &phdr_data,
        &phdr_size,
        &stack_base,
        &stack_size,
        &flags,
        &argv,
        &argvCnt,
        &envp,
        &envpCnt,
        &dtable,
        &dtableCnt,
        &portarray,
        &portarrayCnt,
        &intarray,
        &intarrayCnt);

    int wrote;
    io_write(dtable[1], "Hello Hurd!\n", 12, 0, &wrote);

    proc_mark_exit(portarray[INIT_PORT_PROC], 0 << 8, 0);
    task_terminate(mach_task_self());
}
