#define SAVE_SCREEN

#define USE_TI92PLUS

#include <intr.h>
#include <kbd.h>
#include <link.h>
#include <stdio.h>
#include <system.h>

#include "i68soyuz.h"

INT_HANDLER save_int_1;
INT_HANDLER save_int_5;

volatile char break_key_pressed;
unsigned char keymap[11] = {0};

void setup(void) {
    // ---------------save the default interrupt handlers---------------

    save_int_1 = GetIntVec(AUTO_INT_1); // heartbeat/key scan timer
    save_int_5 = GetIntVec(AUTO_INT_5); // system timer
}

void disable_ints(void) {
    // ---------------override the default interrupt handlers---------------

    SetIntVec(AUTO_INT_1, DUMMY_HANDLER); // heartbeat/key scan timer
    SetIntVec(AUTO_INT_5, DUMMY_HANDLER); // system timer
}

void restore_ints(void) {
    // ---------------restore the default interrupt handlers---------------

    SetIntVec(AUTO_INT_1, save_int_1); // heartbeat/key scan timer
    SetIntVec(AUTO_INT_5, save_int_5); // system timer
}

int version_check() {
    unsigned short send_error = LIO_SendData(SOYUZ_VER, sizeof(SOYUZ_VER));
    if (send_error) {
        printf("Error sending data: %d\n", send_error);
    }

    unsigned char apollo_ver[3] = {0};

    unsigned short recv_error = LIO_RecvData(apollo_ver, sizeof(apollo_ver), 20); // wait 1 second/20 timer ticks
    if (recv_error) {
        printf("Error sending data: %d\n", send_error);
    }

    printf("apollo: %d.%d.%d\n", apollo_ver[MAJOR], apollo_ver[MINOR], apollo_ver[PATCH]);

    return (apollo_ver[MAJOR] == SOYUZ_VER[MAJOR] && apollo_ver[MINOR] == SOYUZ_VER[MINOR]);
}

void run(void) {
    while (1) {

        disable_ints();

        for (int j = 0; j <= 9; j++) {
            keymap[j] = (unsigned char)_rowread(~((short)(1<<j)));
        }

        restore_ints();

        keymap[10] = OSCheckBreak();

        unsigned short send_error = LIO_SendData(keymap, sizeof(keymap));
        if (send_error) {
            printf("Error sending data: %d\n", send_error);
        }

        if (keymap[10]) {
            return;
        }

        idle();
    }
}

void _main(void) {
    clrscr();
    printf("i68 foreign component \"soyuz\"\n\nVersion: %d.%d.%d\nStart apollo\nThen press any key\n",
           SOYUZ_VER[MAJOR],
           SOYUZ_VER[MINOR],
           SOYUZ_VER[PATCH]);

    GKeyIn(NULL, GKF_NORMAL); // wait for input

    LIO_SendData(&READY_BYTE, sizeof(READY_BYTE));
    printf("Started.\n");

    if (!version_check()) {
        printf("verchk fail, aborting\n");
        return;
    }

    printf("Press ON at any time to quit.\n");

    setup();
    run();
    restore_ints(); // just in case
}
