// i68_sys_wait_for_input() -- Alias for a platform-specific wait-for-keycode function. Returns said keycode, though the
// type isn't guaranteed by i68s_sys, neither are the meanings of any given keycodes.

#ifndef I68S_SYS_INPUT_H
#define I68S_SYS_INPUT_H

#if defined(USE_TI92PLUS) || defined(USE_TI89)

#include <kbd.h>

#define i68s_sys_clear_keys GKeyFlush
#define i68s_sys_wait_for_input() GKeyIn(NULL, GKF_NORMAL)

#endif

#if defined(__TI83p__)

#include <stdio.h>

#define i68s_sys_wait_for_input getk

#endif

#endif
