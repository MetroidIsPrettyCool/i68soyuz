// i68s_sys_idle() -- Place calculator into a low power state and waste time. On z80 systems this inlines to a halt
// instruction, on 68k-based systems this is a ROM call of some sort, TI doesn't document how it works internally. One
// suspects it's just STOP.

#ifndef I68S_SYS_IDLE_H
#define I68S_SYS_IDLE_H

#if defined(USE_TI92PLUS) || defined(USE_TI89)

#include <system.h>

void i68s_sys_idle(void);

#endif

#if defined(__TI83p__)

#define i68s_sys_idle() __asm__("halt")

#endif

#endif
