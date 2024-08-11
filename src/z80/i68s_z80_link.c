#include "i68s_sys_link.h"

#include "i68s_z80_link.h"

unsigned short i68s_sys_send_bytes(const void* src, unsigned short size) {
    static unsigned short i;
    for (i = 0; i != size; i++) {
        send_byte(((unsigned char*)src)[i]);
    }
    return 0;
}

unsigned short i68s_sys_receive_bytes(void* dest, unsigned short size, unsigned short WaitDelay) {
    static unsigned short i;
    for (i = 0; i != size; i++) {
        ((unsigned char*)dest)[i] = recv_byte();
    }
    return 0;
}
