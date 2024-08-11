CC=tigcc
CFLAGS=-std=c99 -O2 -Wall -Wextra -I./src/system

SRCDIR=./src/core/

CFILENAMES=i68soyuz i68s_handshake i68s_read_kbd
HFILENAMES=i68soyuz i68s_handshake i68s_read_kbd i68s_version

CFILES=$(addprefix $(SRCDIR),$(addsuffix .c,$(CFILENAMES)))
HFILES=$(addprefix $(SRCDIR),$(addsuffix .h,$(HFILENAMES)))

.PHONY: clean all

all: ./bin/i68soyuz.9xz # ./bin/i68soyuz.89z

./bin/i68soyuz.9xz: $(CFILES) $(HFILES) ./src/68k/i68s_68k_interrupts.c
	$(CC) $(CFLAGS) -DSAVE_SCREEN -DUSE_TI92PLUS -o $@ $(CFILES) ./src/68k/i68s_68k_interrupts.c

# ./bin/i68soyuz.89z: $(CFILES) $(HFILES)
# 	$(CC) $(CFLAGS) -DSAVE_SCREEN -DUSE_TI89 -o $@ $(CFILES)

clean:
	rm ./bin/i68soyuz.9xz # ./bin/i68soyuz.89z
