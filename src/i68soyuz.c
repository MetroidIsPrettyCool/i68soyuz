#define SAVE_SCREEN

#include <intr.h>
#include <kbd.h>
#include <link.h>
#include <stdio.h>
#include <system.h>

#include "i68s_interrupts.h"
#include "i68s_handshake.h"
#include "i68s_version.h"

// header file containing platform-specific definitions
#include "i68s_compat.h"

#include "i68soyuz.h"

void setup(void) {
    setup_ints();

    clrscr();
}

void cleanup(void) {
    cleanup_ints();

    GKeyFlush();
}

void run(void) {
    printf("i68 foreign component\n\"soyuz\"\n\n"
           "Version %d.%d.%d\n"
           "Built %s %s\n\n"
           "Start apollo then press\n"
           "any key to continue\n\n"
           "Or press ON to abort\n",
           SOYUZ_VER[MAJOR],
           SOYUZ_VER[MINOR],
           SOYUZ_VER[PATCH],
           __DATE__,
           __TIME__);

    GKeyIn(NULL, GKF_NORMAL); // wait for input
    if (OSCheckBreak()) {
        return;
    }

    printf("\nHandshaking...\n");

    struct I68Config i68_config = handshake();
    switch (i68_config.handshake_result) {

    case HANDSHAKE_VERSION_MISMATCH:
        printf("Version mismatch\n"
               "apollo ver: %d.%d.%d\n\n"
               "Press any key to exit\n",
               i68_config.apollo_version[MAJOR],
               i68_config.apollo_version[MINOR],
               i68_config.apollo_version[PATCH]);
        GKeyIn(NULL, GKF_NORMAL); // wait for input
        return;

    case HANDSHAKE_WRITE_ERROR:
        printf("Handshake write error\n\n"
               "Press any key to exit\n");
        GKeyIn(NULL, GKF_NORMAL); // wait for input
        return;

    case HANDSHAKE_READ_ERROR:
        printf("Handshake read error\n\n"
               "Press any key to exit\n");
        GKeyIn(NULL, GKF_NORMAL); // wait for input
        return;

    default:
        printf("Unhandled handshake error\n\n"
               "Press any key to exit\n");
        GKeyIn(NULL, GKF_NORMAL); // wait for input
        return;

    case HANDSHAKE_SUCCESS:
        printf("Handshake success\n\n"
               "apollo ver: %d.%d.%d\n\n",
               i68_config.apollo_version[MAJOR],
               i68_config.apollo_version[MINOR],
               i68_config.apollo_version[PATCH]);
        break;
    }

    printf("Press ON at any time to quit.\n");

    keymatrix_loop();
}

unsigned char key_matrix_state[KEY_MATRIX_HEIGHT];
unsigned char prev_key_matrix_state[KEY_MATRIX_HEIGHT];

void read_key_matrix_state(void) {
    // read key matrix
    disable_ints15();

    for (unsigned int i = 0; i < sizeof(key_matrix_state); i++) {
        key_matrix_state[i] = (unsigned char)_rowread(~((short)(1<<i)));
    }

    restore_ints15();

    // handle "ON" key
    key_matrix_state[BREAK_KEY_ROW] |= read_break_key(); // row 1 bit 0 is unused, so we'll stick the break key status here
}

void keymatrix_loop(void) {
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

        if (key_matrix_state[BREAK_KEY_ROW] & (1 << BREAK_KEY_COL)) {
            return;
        }

        idle();
    }
}

void _main(void) {
    setup();

    run();

    cleanup();
}
