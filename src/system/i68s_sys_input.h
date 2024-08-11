// i68_sys_clear_keys() -- flush keyqueue
//
// i68_sys_wait_for_input() -- wait for keypress

#ifndef I68S_SYS_INPUT_H
#define I68S_SYS_INPUT_H

#if defined(USE_TI92PLUS)

#include <kbd.h>

#define i68s_sys_clear_keys GKeyFlush
#define i68s_sys_wait_for_input() GKeyIn(NULL, GKF_NORMAL)

#endif

#endif
