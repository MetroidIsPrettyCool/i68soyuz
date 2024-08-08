#include <link.h>
#include <stdio.h>

#include "i68s_version.h"

#include "i68s_handshake.h"

const unsigned char READY_BYTE = 0x50;

struct I68Config handshake(void) {
    struct I68Config i68_config;

    unsigned short rdy_error = LIO_SendData(&READY_BYTE, sizeof(READY_BYTE));
    if (rdy_error) {
        i68_config.handshake_result = HANDSHAKE_WRITE_ERROR;
        return i68_config;
    }

    unsigned short send_error = LIO_SendData(SOYUZ_VER, sizeof(SOYUZ_VER));
    if (send_error) {
        i68_config.handshake_result = HANDSHAKE_WRITE_ERROR;
        return i68_config;
    }

    unsigned short recv_error = LIO_RecvData(i68_config.apollo_version, sizeof(i68_config.apollo_version), 20); // timeout of 1 second/20 timer ticks
    if (recv_error) {
        i68_config.handshake_result = HANDSHAKE_READ_ERROR;
        return i68_config;
    }

    // i68_config.apollo_version is now initialized

    if (i68_config.apollo_version[MAJOR] != SOYUZ_VER[MAJOR] || i68_config.apollo_version[MINOR] != SOYUZ_VER[MINOR]) {
        i68_config.handshake_result = HANDSHAKE_VERSION_MISMATCH;
        return i68_config;
    }

    // everything checks out!

    i68_config.handshake_result = HANDSHAKE_SUCCESS;
    return i68_config;
}