VPATH = ../../src/core ../../src/system

CFLAGS += -std=c99 -O2 -Wall -Wextra -I../../src/system

OBJFILES = i68soyuz.o i68s_handshake.o i68s_read_kbd.o
