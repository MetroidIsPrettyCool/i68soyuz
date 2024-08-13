// Defines a one-byte constant MACHINE_ID to identify a given build of i68soyuz during handshake.
//
// In general, IDs for non-plus calculators are simply the model number, e.g. the TI-89 is MACHINE_ID 89. "Plus" model
// calculators are the model number + 100. Deviations from this pattern will be dealt on a case-by-case basis, should
// the need arise. For example: the TI-92 II, which I will almost certainly never own, could be assigned the ID 93 (92 +
// 1) since there isn't any calculator with the designation TI-93.

#ifndef I68S_SYS_MACHINE_H
#define I68S_SYS_MACHINE_H

#ifdef USE_TI92PLUS

#define MACHINE_ID 192;

#endif

#ifdef USE_TI89

#define MACHINE_ID 89;

#endif

#ifdef __TI83p__

#define MACHINE_ID 183;

#endif

#endif
