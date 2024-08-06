#include <intr.h>

#include "i68s_interrupts.h"

INT_HANDLER save_int_1;
INT_HANDLER save_int_5;

void setup_ints(void) {
    // save the default interrupt handlers
    save_int_1 = GetIntVec(AUTO_INT_1); // heartbeat/key scan timer
    save_int_5 = GetIntVec(AUTO_INT_5); // system timer
}

void disable_ints(void) {
    // override the default interrupt handlers
    SetIntVec(AUTO_INT_1, DUMMY_HANDLER); // heartbeat/key scan timer
    SetIntVec(AUTO_INT_5, DUMMY_HANDLER); // system timer
}

void restore_ints(void) {
    // restore the default interrupt handlers
    SetIntVec(AUTO_INT_1, save_int_1); // heartbeat/key scan timer
    SetIntVec(AUTO_INT_5, save_int_5); // system timer
}
