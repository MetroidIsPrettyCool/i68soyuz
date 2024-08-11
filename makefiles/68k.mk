include ../../makefiles/commonvars.mk

VPATH += ../../src/68k
CC = tigcc
CFLAGS += -std=c99 -DSAVE_SCREEN

OBJFILES += i68s_68k_interrupts.o

$(OUTFILE): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

include ../../makefiles/commondependancies.mk

i68s_68k_interrupts.o: i68s_sys_break.h i68s_sys_setup_cleanup.h i68s_sys_matrix.h

clean:
	rm -f $(OUTFILE) $(OBJFILES)
