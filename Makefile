CC=tigcc
CFLAGS=-std=c99 -O2 -Wall -Wextra

SRCDIR=./src/

CFILENAMES=i68soyuz i68s_interrupts i68s_handshake
HFILENAMES=i68soyuz i68s_interrupts i68s_handshake i68s_meta

CFILES=$(addprefix $(SRCDIR),$(addsuffix .c,$(CFILENAMES)))
HFILES=$(addprefix $(SRCDIR),$(addsuffix .h,$(HFILENAMES)))

.PHONY: clean all

all: ./bin/i68soyuz.9xz ./bin/i68soyuz.89z

./bin/i68soyuz.9xz: $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) -DUSE_TI92PLUS -o $@ $(CFILES)

./bin/i68soyuz.89z: $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) -DUSE_TI89 -o $@ $(CFILES)

clean:
	rm ./bin/i68soyuz.9xz ./bin/i68soyuz.89z
