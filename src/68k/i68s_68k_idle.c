#include <system.h>

#include "i68s_sys_idle.h"

void i68s_sys_idle(void) {
    for (int i = 0; i != 8; i++) {
        idle();
    }
}
