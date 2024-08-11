VPATH = ../../src/core ../../src/system ../../src/68k
CC = tigcc
CFLAGS += -std=c99 -O2 -Wall -Wextra -I../../src/system -DSAVE_SCREEN

OBJFILES = i68soyuz.o i68s_handshake.o i68s_read_kbd.o i68s_68k_interrupts.o

.PHONY: clean

$(OUTFILE): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OUTFILE) $(OBJFILES)
