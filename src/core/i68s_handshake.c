#include "i68s_sys_link.h"
#include "i68s_sys_machine.h"

#include "i68s_version.h"

#include "i68s_handshake.h"

const unsigned char READY_BYTE = 0x50;

const unsigned char MACHINE_ID_BYTE = MACHINE_ID;

struct I68Config i68_config;

struct I68Config* handshake(void) {
    unsigned short link_error;

    link_error = i68s_sys_send_bytes(&READY_BYTE, sizeof(READY_BYTE));
    if (link_error) {
        i68_config.handshake_result = HANDSHAKE_WRITE_ERROR;
        return &i68_config;
    }

    link_error = i68s_sys_send_bytes(SOYUZ_VER, sizeof(SOYUZ_VER));
    if (link_error) {
        i68_config.handshake_result = HANDSHAKE_WRITE_ERROR;
        return &i68_config;
    }

    link_error = i68s_sys_receive_bytes(i68_config.apollo_version, sizeof(i68_config.apollo_version));
    if (link_error) {
        i68_config.handshake_result = HANDSHAKE_READ_ERROR;
        return &i68_config;
    }

    // i68_config.apollo_version is now initialized

    if (i68_config.apollo_version[MAJOR] != SOYUZ_VER[MAJOR] || i68_config.apollo_version[MINOR] != SOYUZ_VER[MINOR]) {
        i68_config.handshake_result = HANDSHAKE_VERSION_MISMATCH;
        return &i68_config;
    }

    // transmit machine ID

    link_error = i68s_sys_send_bytes(&MACHINE_ID_BYTE, sizeof(MACHINE_ID_BYTE));
    if (link_error) {
        i68_config.handshake_result = HANDSHAKE_WRITE_ERROR;
        return &i68_config;
    }

    // everything checks out!

    i68_config.handshake_result = HANDSHAKE_SUCCESS;
    return &i68_config;
}
