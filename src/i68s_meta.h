#ifndef I68S_META_H
#define I68S_META_H

#define MAJOR 0
#define MINOR 1
#define PATCH 2

const unsigned char SOYUZ_VER[3] = {0, 5, 0};

#ifdef USE_TI92PLUS

#define KEY_MATRIX_HEIGHT 10

// Row and Column of an empty slot in the key matrix where we'll stuff the break key state
#define BREAK_KEY_ROW 1
#define BREAK_KEY_COL 0

// If I ever add support for the original TI-92, it'll be ID 92. The TI-92 II, which I will almost certainly never own,
// would be ID 93.
const unsigned char MACHINE_ID = 192;

#endif

#ifdef USE_TI89

#define KEY_MATRIX_HEIGHT 7

// Row and Column of an empty slot in the key matrix where we'll stuff the break key state
#define BREAK_KEY_ROW 6
#define BREAK_KEY_COL 7

const unsigned char MACHINE_ID = 89;

#endif

#endif
