#include "i68s_sys_break.h"
#include "i68s_sys_idle.h"
#include "i68s_sys_input.h"
#include "i68s_sys_link.h"
#include "i68s_sys_matrix.h"
#include "i68s_sys_output.h"

#include "i68s_interrupts.h"
#include "i68s_handshake.h"
#include "i68s_read_kbd.h"

#include "i68s_meta.h"

#include "i68soyuz.h"

void setup(void) {
    setup_ints();

    i68s_sys_clear_screen();
}

void cleanup(void) {
    cleanup_ints();

    i68s_sys_clear_keys();
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

    i68s_sys_wait_for_input(); // wait for input
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
        i68s_sys_wait_for_input(); // wait for input
        return;

    case HANDSHAKE_WRITE_ERROR:
        printf("Handshake write error\n\n"
               "Press any key to exit\n");
        i68s_sys_wait_for_input(); // wait for input
        return;

    case HANDSHAKE_READ_ERROR:
        printf("Handshake read error\n\n"
               "Press any key to exit\n");
        i68s_sys_wait_for_input(); // wait for input
        return;

    default:
        printf("Unhandled handshake error\n\n"
               "Press any key to exit\n");
        i68s_sys_wait_for_input(); // wait for input
        return;

    case HANDSHAKE_SUCCESS:
        printf("Handshake success\n\n"
               "apollo ver: %d.%d.%d\n\n",
               i68_config.apollo_version[MAJOR],
               i68_config.apollo_version[MINOR],
               i68_config.apollo_version[PATCH]);
        break;
    }

    printf("Press ON at any time\nto quit\n");

    keymatrix_loop();
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

        unsigned short send_error = i68s_sys_send_bytes(key_matrix_state, sizeof(key_matrix_state));
        if (send_error) {
            printf("Error sending data: %d\n", send_error);
        }

        if (key_matrix_state[BREAK_KEY_ROW] & (1 << BREAK_KEY_COL)) {
            return;
        }

        i68s_sys_idle();
    }
}

void _main(void) {
    setup();

    run();

    cleanup();
}