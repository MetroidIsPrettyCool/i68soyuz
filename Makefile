CC=tigcc
CFLAGS=-std=c99 -O2 -Wall -Wextra -I.

SRCDIR=./src/
CFILES=$(SRCDIR)i68soyuz.c $(SRCDIR)i68s_interrupts.c $(SRCDIR)i68s_handshake.c
HFILES=$(SRCDIR)i68soyuz.h $(SRCDIR)i68s_interrupts.h $(SRCDIR)i68s_handshake.h

.PHONY: clean

./bin/i68soyuz.9xz: $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) -o $@ $(CFILES)

clean:
	rm ./bin/i68soyuz.9xz
