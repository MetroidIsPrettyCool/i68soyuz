// i68s_sys_send_bytes() -- send bytes from link port
//
// i68s_sys_receive_bytes() -- receive bytes from link port

#ifndef I68S_SYS_LINK_H
#define I68S_SYS_LINK_H

#if defined(USE_TI92PLUS)

#include <link.h>

#define i68s_sys_send_bytes LIO_SendData
#define i68s_sys_receive_bytes LIO_RecvData

#endif

#endif
