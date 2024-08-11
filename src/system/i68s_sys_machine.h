// defines constant MACHINE_ID

#ifndef I68S_SYS_MACHINE_H
#define I68S_SYS_MACHINE_H

#ifdef USE_TI92PLUS

// If I ever add support for the original TI-92, it'll be ID 92. The TI-92 II, which I will almost certainly never own,
// would be ID 93.
const unsigned char MACHINE_ID = 192;

#endif

/* #ifdef USE_TI89 */

/* const unsigned char MACHINE_ID = 89; */

/* #endif */

#endif
