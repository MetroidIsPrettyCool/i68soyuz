#define SAVE_SCREEN

#define USE_TI92PLUS

#include <intr.h>
#include <kbd.h>
#include <link.h>
#include <stdio.h>
#include <system.h>

INT_HANDLER save_int_1;
INT_HANDLER save_int_5;
INT_HANDLER save_int_6;

volatile char break_key_pressed;
unsigned char keymap[32] = {0};

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

void _main(void) {
    clrscr();
    printf("i68 foreign component \"soyuz\"\n\nBuild 28\nPress any key to begin...\n");
    ngetchx();
    printf("Started.\nPress ON at any time to quit.\n");

    setup();
    run();
    cleanup();
}
