VPATH = ../../src/core ../../src/system ../../src/68k
CC = tigcc
CFLAGS += -std=c99 -O2 -Wall -Wextra -I../../src/system -DSAVE_SCREEN

OBJFILES = i68soyuz.o i68s_handshake.o i68s_read_kbd.o i68s_68k_interrupts.o

.PHONY: clean

$(OUTFILE): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

i68soyuz.o: i68s_sys_break.h i68s_sys_idle.h i68s_sys_input.h i68s_sys_interrupts.h i68s_sys_link.h i68s_sys_matrix.h i68s_sys_output.h i68s_handshake.h i68s_read_kbd.h i68s_version.h i68soyuz.h
i68s_handshake.o: i68s_sys_link.h i68s_sys_machine.h i68s_version.h i68s_handshake.h
i68s_read_kbd.o: i68s_sys_break.h i68s_sys_interrupts.h i68s_sys_matrix.h i68s_read_kbd.h
i68s_68l_interrupts.o: i68s_sys_break.h i68s_sys_interrupts.h i68s_sys_matrix.h

clean:
	rm -f $(OUTFILE) $(OBJFILES)
