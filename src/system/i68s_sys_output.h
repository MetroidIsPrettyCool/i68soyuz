// i68_sys_clear_screen() -- an alias for whatever library call is used to clear the screen
//
// i68_sys_printf() -- an alias for whatever library call is used for formatted output

#ifndef I68S_SYS_OUTPUT_H
#define I68S_SYS_OUTPUT_H

#if defined(USE_TI92PLUS) || defined(USE_TI89)

#include <stdio.h>

#define i68s_sys_clear_screen clrscr
#define i68s_sys_printf printf

#endif

#endif
