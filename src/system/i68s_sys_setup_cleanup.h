// void i68s_sys_setup(void) -- Platform-specific setup function. Used to override interrupts, clear the screen, etc.
//
// void i68s_sys_cleanup(void) -- Platform-specific cleanup function. Used to restore interrupts, clear the screen, etc.

#ifndef I68S_SYS_INTERRUPTS_H
#define I68S_SYS_INTERRUPTS_H

void i68_sys_setup(void);

void i68_sys_cleanup(void);

#endif
