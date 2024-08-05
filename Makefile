CC=tigcc
CFLAGS=-std=c99 -O2 -Wall -Wextra -I.

SRCDIR=./src/
CFILES=$(SRCDIR)i68soyuz.c
HFILES=$(SRCDIR)i68soyuz.h

.PHONY: clean

./bin/i68soyuz.9xz: $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) -o $@ $(CFILES)

clean:
	rm ./bin/i68soyuz.9xz
