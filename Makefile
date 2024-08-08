CC=tigcc
CFLAGS=-std=c99 -O2 -Wall -Wextra

SRCDIR=./src/

CFILENAMES=i68soyuz i68s_interrupts i68s_handshake
HFILENAMES=i68soyuz i68s_interrupts i68s_handshake i68s_version i68s_compat

CFILES=$(addprefix $(SRCDIR),$(addsuffix .c,$(CFILENAMES)))
HFILES=$(addprefix $(SRCDIR),$(addsuffix .h,$(HFILENAMES)))

.PHONY: clean all

all: ./bin/i68soyuz.9xz ./bin/i68soyuz.89z

./bin/i68soyuz.9xz: $(CFILES) $(HFILES) $(SRCDIR)i68s_ti92p_native.h
	$(CC) $(CFLAGS) -DUSE_TI92PLUS -o $@ $(CFILES)

./bin/i68soyuz.89z: $(CFILES) $(HFILES) $(SRCDIR)i68s_ti89_native.h
	$(CC) $(CFLAGS) -DUSE_TI89 -o $@ $(CFILES)

clean:
	rm ./bin/i68soyuz.9xz ./bin/i68soyuz.89z
