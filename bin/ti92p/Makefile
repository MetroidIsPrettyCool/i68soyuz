VPATH = ../../src/core ../../src/system ../../src/68k
CC = tigcc
CFLAGS = -std=c99 -O2 -Wall -Wextra -I../../src/system -DSAVE_SCREEN -DUSE_TI92PLUS

.PHONY: clean

i68soyuz.9xz: i68soyuz.o i68s_handshake.o i68s_read_kbd.o i68s_68k_interrupts.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm i68soyuz.9xz *.o
