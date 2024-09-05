        INCLUDE "Ti83p.def"	; ROM / RAM adresses on Ti83+[SE]

_i68s_sys_reset_apd:
        GLOBAL _i68s_sys_reset_apd
        INVOKE _ApdSetup
        ret

_i68s_sys_read_loop_setup:
        GLOBAL _i68s_sys_read_loop_setup
        push af
        push hl
        INVOKE _EnableApd
        ld a, (IY + 8)
        or 0b1100
        ld (IY + 8), a
        pop hl
        pop af
        ret
