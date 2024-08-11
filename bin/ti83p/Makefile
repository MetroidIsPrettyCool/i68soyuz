include ../../makefiles/commonvars.mk

VPATH += ../../src/z80
CC = zcc
CFLAGS += +ti83p -subtype=asm -pragma-define:CRT_ENABLE_STDIO=0 # -pragma-define:GimmeSpeed
LDFLAGS = $(CFLAGS)

AS = z88dk-z80asm
ASFLAGS = -mti83plus -I$(ZCCCFG)/../target/ti83p/def # ugly, works

OBJFILES += i68s_z80_break.o i68s_z80_link_bytes.o i68s_z80_link.o i68s_z80_matrix.o i68s_z80_setup_cleanup.o

i68soyuz.8xp: i68soyuz
	z88dk-appmake +ti8x -o $@ -b $^

i68soyuz: $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

include ../../makefiles/commondependancies.mk

# z88dk-z80asm automatically named the object files it produces, and doesn't support the -c flag, so we have to override
# the default rule for .s files here
%.o: %.s
	$(AS) $(ASFLAGS) -o$@ $^

i68s_z80_link.o: i68s_sys_link.h i68s_z80_link.h
i68s_z80_setup_cleanup.o: i68s_sys_setup_cleanup.h

clean:
	rm -f $(OUTFILE) $(OBJFILES)
