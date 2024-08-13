// unsigned short i68s_sys_send_bytes() -- Send bytes from link port. May return non-zero upon failure.
//
// unsigned short i68s_sys_receive_bytes() -- Receive bytes from link port. May return non-zero upon failure.

#ifndef I68S_SYS_LINK_H
#define I68S_SYS_LINK_H

#if defined(USE_TI92PLUS) || defined(USE_TI89)

#include <link.h>

#define i68s_sys_send_bytes LIO_SendData
#define i68s_sys_receive_bytes(dest, size) LIO_RecvData(dest, size, 20)

#endif

#if defined(__TI83p__)

unsigned short i68s_sys_send_bytes(const void* src, unsigned short size);
unsigned short i68s_sys_receive_bytes(void* dest, unsigned short size);

#endif

#endif
