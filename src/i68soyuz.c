#define SAVE_SCREEN

#define USE_TI92PLUS

#include <intr.h>
#include <kbd.h>
#include <link.h>
#include <stdio.h>
#include <system.h>

#define MAJOR 0
#define MINOR 1
#define PATCH 2

INT_HANDLER save_int_1;
INT_HANDLER save_int_5;
INT_HANDLER save_int_6;

const unsigned char SOYUZ_VER[3] = {0, 3, 1};
const unsigned char READY_BYTE = 0x50;

volatile char break_key_pressed;
unsigned char keymap[11] = {0};

DEFINE_INT_HANDLER(OnBreakKey) {
    break_key_pressed = 1;
}

void print_byte(unsigned char byte) {
    printf("%d%d%d%d%d%d%d%d\n",
           (byte >> 7 & 1),
           (byte >> 6 & 1),
           (byte >> 5 & 1),
           (byte >> 4 & 1),
           (byte >> 3 & 1),
           (byte >> 2 & 1),
           (byte >> 1 & 1),
           (byte      & 1));
}

void setup(void) {
    // ---------------other---------------

    break_key_pressed = 0;

    // ---------------save the default interrupt handlers---------------

    save_int_1 = GetIntVec(AUTO_INT_1);
    save_int_5 = GetIntVec(AUTO_INT_5);
    save_int_6 = GetIntVec(AUTO_INT_6);

    // ---------------set global variables---------------

    // override automatic interrupt handlers 1 (heartbeat timer/keyscan)...
    SetIntVec(AUTO_INT_1, DUMMY_HANDLER);
    // ..and 5 (system timer)...
    SetIntVec(AUTO_INT_5, DUMMY_HANDLER);
    // ...and 6 (on key)
    SetIntVec(AUTO_INT_6, OnBreakKey);
}

void cleanup(void) {
    // ---------------restore the default interrupt handlers---------------

    SetIntVec(AUTO_INT_1, save_int_1);
    SetIntVec(AUTO_INT_5, save_int_5);
    SetIntVec(AUTO_INT_6, save_int_6);
}

void run(void) {
    unsigned char tmp;

    while (1) {

        for (int j = 0; j <= 9; j++) {
            keymap[j] = (unsigned char)_rowread(~((short)(1<<j)));
        }
        keymap[10] = break_key_pressed;

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

int version_check() {
    LIO_SendData(SOYUZ_VER, sizeof(SOYUZ_VER));

    unsigned char apollo_ver[3] = {0};
    LIO_RecvData(apollo_ver, sizeof(apollo_ver), 20); // wait 1 second/20 timer ticks

    printf("apollo: %d.%d.%d\n", apollo_ver[MAJOR], apollo_ver[MINOR], apollo_ver[PATCH]);

    return (apollo_ver[MAJOR] == SOYUZ_VER[MAJOR] && apollo_ver[MINOR] == SOYUZ_VER[MINOR]);
}

void _main(void) {
    clrscr();
    printf("i68 foreign component \"soyuz\"\n\nVersion: %d.%d.%d\nStart apollo\nThen press any key\n",
           SOYUZ_VER[MAJOR],
           SOYUZ_VER[MINOR],
           SOYUZ_VER[PATCH]);
    ngetchx();

    LIO_SendData(&READY_BYTE, sizeof(READY_BYTE));
    printf("Started.\n");

    if (!version_check()) {
        printf("verchk fail, aborting\n");
        return;
    }
    printf("Press ON at any time to quit.\n");

    setup();
    run();
    cleanup();
}
