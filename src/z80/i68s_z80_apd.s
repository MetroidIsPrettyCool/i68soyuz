        INCLUDE "Ti83p.def"	; ROM / RAM adresses on Ti83+[SE]

_i68s_sys_reset_apd:
        GLOBAL _i68s_sys_reset_apd
        INVOKE _ApdSetup
        ret

        ;; copy-pasted from https://jgmalcolm.com/z80/advanced/onof, unsure of exactly how it works
_i68s_sys_off:
        GLOBAL _i68s_sys_off
        ld a,1
        out (3),a
        halt
        ld a,11
        out (3),a
        ret

_i68s_sys_apd_expired:
        GLOBAL _i68s_sys_apd_expired
        ld a, ($8449)
        or a
        ld l, 0
        jp NZ, skip
        ld l, 1
skip:
        ret
