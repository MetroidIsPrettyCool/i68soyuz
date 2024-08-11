#ifndef I68S_Z80_LINK_H
#define I68S_Z80_LINK_H

unsigned char recv_byte(void)  __naked;
void send_byte(unsigned char) __z88dk_fastcall __naked;

#endif
