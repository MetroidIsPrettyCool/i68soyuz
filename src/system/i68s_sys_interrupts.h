// i68s_sys_get_interrupt_vector(x)
//
// i68s_sys_set_interrupt_vector(x)

#ifndef I68S_SYS_INTERRUPTS_H
#define I68S_SYS_INTERRUPTS_H

#if defined(USE_TI92PLUS)

#include <intr.h>

#define i68s_sys_get_interrupt_vector GetIntVec
#define i68s_sys_set_interrupt_vector SetIntVec

#endif

#endif
