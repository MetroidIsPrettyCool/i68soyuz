// i68s_sys_reset_apd() -- reset Automatic Power Down timer
//
// unsigned char i68s_sys_apd_expired() -- return 1 if the Automatic Power Down timer has expired, else 0
//
// i68s_sys_off() -- poweroff calculator

#ifndef I68S_SYS_APD_H
#define I68S_SYS_APD_H

#if defined(USE_TI92PLUS) || defined(USE_TI89)

#include <system.h>

#define i68s_sys_off off
#define i68s_sys_reset_apd() OSTimerRestart(APD_TIMER)
#define i68s_sys_apd_expired() OSTimerExpired(APD_TIMER)

#endif

#if defined(__TI83p__)

void i68s_sys_off(void);
void i68s_sys_reset_apd(void);
unsigned char i68s_sys_apd_expired(void);

#endif

#endif
