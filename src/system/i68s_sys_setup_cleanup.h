// void i68s_sys_setup(void) -- Platform-specific setup function. Used to override interrupts, clear the screen, etc.
//
// void i68s_sys_cleanup(void) -- Platform-specific cleanup function. Used to restore interrupts, clear the screen, etc.
//
// i68s_sys_read_loop_setup() -- Platform-specific setup for the read loop; stuff like masking interrupts, etc.

#ifndef I68S_SYS_INTERRUPTS_H
#define I68S_SYS_INTERRUPTS_H

void i68_sys_setup(void);

void i68_sys_cleanup(void);

#if defined(USE_TI92PLUS) || defined(USE_TI89)

#define i68s_sys_read_loop_setup() OSSetSR(0x0100)

#endif

#if defined(__TI83p__)

void i68s_sys_read_loop_setup(void) __naked;

#endif

#endif
