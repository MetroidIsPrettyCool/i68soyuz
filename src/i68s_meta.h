#ifndef I68S_META_H
#define I68S_META_H

#ifdef USE_TI92PLUS

// If I ever add support for the original TI-92, it'll be ID 92. The TI-92 II, which I will almost certainly never own,
// would be ID 93.
const unsigned char MACHINE_ID = 192;

#endif

#ifdef USE_TI89

const unsigned char MACHINE_ID = 89;

#endif

#define MAJOR 0
#define MINOR 1
#define PATCH 2

const unsigned char SOYUZ_VER[3] = {0, 5, 0};

#endif
