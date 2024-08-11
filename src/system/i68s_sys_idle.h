// i68s_sys_idle -- place calculator into "idle" state

#ifndef I68S_SYS_IDLE_H
#define I68S_SYS_IDLE_H

#if defined(USE_TI92PLUS) || defined(USE_TI89)

#include <system.h>

#define i68s_sys_idle idle

#endif

#if defined(__TI83p__)

#define i68s_sys_idle() __asm__("halt")

#endif

#endif
