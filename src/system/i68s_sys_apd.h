// i68s_sys_reset_apd() -- reset Automatic Power Down timer
//
// unsigned char i68s_sys_apd_expired() -- return 1 if the Automatic Power Down timer has expired, else 0
//
// i68s_sys_off() -- poweroff calculator

#ifndef I68S_SYS_APD_H
#define I68S_SYS_APD_H

#if defined(USE_TI92PLUS) || defined(USE_TI89)

#include <system.h>

void i68s_sys_off(void);
#define i68s_sys_reset_apd() OSTimerRestart(APD_TIMER)
#define i68s_sys_apd_expired() OSTimerExpired(APD_TIMER)

#endif

#if defined(__TI83p__)

/* void i68s_sys_off(void) __naked; */
void i68s_sys_reset_apd(void) __naked;
/* unsigned char i68s_sys_apd_expired(void) __naked; */

/* #define i68s_sys_off() ; */
/* #define i68s_sys_apd_expired() !*((unsigned short*)0x8448) */

// the "powering off" part of APD is handled by TIOS on the TI-83 Plus
#define i68s_sys_off() ;
#define i68s_sys_apd_expired() 0

#endif

#endif
