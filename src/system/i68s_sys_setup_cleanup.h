// i68s_sys_setup()
//
// i68s_sys_cleanup()

#ifndef I68S_SYS_INTERRUPTS_H
#define I68S_SYS_INTERRUPTS_H

/* #if defined(USE_TI92PLUS) */

/* #include <intr.h> */

/* #define i68s_sys_get_interrupt_vector GetIntVec */
/* #define i68s_sys_set_interrupt_vector SetIntVec */

/* #endif */

/* void i68s_sys_setup_interrupts(void); */
/* void i68s_sys_disable_keyboard_interrupts(void); */
/* void i68s_sys_restore_keyboard_interrupts(void); */
/* void i68s_sys_restore_all_interrupts(void); */

void i68_sys_setup(void);

void i68_sys_cleanup(void);

#endif
