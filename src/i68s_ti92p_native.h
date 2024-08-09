#ifndef I86_NATIVE_H
#define I86_NATIVE_H

#define KEY_MATRIX_HEIGHT 10

// Row and Column of an empty slot in the key matrix where we'll stuff the break key state
#define BREAK_KEY_ROW 1
#define BREAK_KEY_COL 0

// If I ever add support for the original TI-92, it'll be ID 92. The TI-92 II, which I will almost certainly never own,
// would be ID 93.
const unsigned char MACHINE_ID = 192;

#endif
