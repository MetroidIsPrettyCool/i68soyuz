#define SAVE_SCREEN

#define USE_TI92PLUS

#include <intr.h>
#include <kbd.h>
#include <link.h>
#include <stdio.h>
#include <system.h>

#include "i68s_interrupts.h"
#include "i68s_handshake.h"
#include "i68s_version.h"

#include "i68soyuz.h"

void setup(void) {
    setup_ints();

    clrscr();
}

void read_key_matrix_state(void) {
    disable_ints();

    for (unsigned int i = 0; i < sizeof(key_matrix_state); i++) {
        key_matrix_state[i] = (unsigned char)_rowread(~((short)(1<<i)));
    }

    restore_ints();

    key_matrix_state[1] |= OSCheckBreak();
}

void run(void) {
    read_key_matrix_state();

    while (1) {

        for (unsigned int i = 0; i < sizeof(key_matrix_state); i++) {
            prev_key_matrix_state[i] = key_matrix_state[i];
        }

        read_key_matrix_state();

        // check key_matrix_states aren't equal
        char key_matrix_states_equal;
        for (unsigned int i = 0; i < sizeof(key_matrix_state); i++) {
            key_matrix_states_equal = (prev_key_matrix_state[i] == key_matrix_state[i]);
            if (!key_matrix_states_equal) {
                break;
            }
        }
        if (key_matrix_states_equal) { // if nothing's changed we don't need to transmit
            continue;
        }

        unsigned short send_error = LIO_SendData(key_matrix_state, sizeof(key_matrix_state));
        if (send_error) {
            printf("Error sending data: %d\n", send_error);
        }

        if (key_matrix_state[1] & 1) {
            return;
        }

        idle();
    }
}

void _main(void) {
    setup();

    printf("i68 foreign component \"soyuz\"\n\n"
           "Version: %d.%d.%d\n"
           "Built %s %s\n"
           "Start apollo\n"
           "Then press any key\n",
           SOYUZ_VER[MAJOR],
           SOYUZ_VER[MINOR],
           SOYUZ_VER[PATCH],
           __DATE__,
           __TIME__);

    GKeyIn(NULL, GKF_NORMAL); // wait for input

    printf("Handshaking...\n");

    struct I68Config i68_config = handshake();
    switch (i68_config.handshake_result) {

    case HANDSHAKE_VERSION_MISMATCH:
        printf("Version mismatch\n"
               "apollo ver: %d.%d.%d\n"
               "Aborting\n",
               i68_config.apollo_version[MAJOR],
               i68_config.apollo_version[MINOR],
               i68_config.apollo_version[PATCH]);
        return;

    case HANDSHAKE_WRITE_ERROR:
        printf("Handshake write error\n"
               "Aborting\n");
        return;

    case HANDSHAKE_READ_ERROR:
        printf("Handshake read error\n"
               "Aborting\n");
        return;

    default:
        printf("Unhandled handshake error\n"
               "Aborting\n");
        return;

    case HANDSHAKE_SUCCESS:
        printf("Success\n"
               "apollo ver: %d.%d.%d\n",
               i68_config.apollo_version[MAJOR],
               i68_config.apollo_version[MINOR],
               i68_config.apollo_version[PATCH]);
        break;
    }

    printf("Press ON at any time to quit.\n");

    run();
    restore_ints(); // just in case
}
