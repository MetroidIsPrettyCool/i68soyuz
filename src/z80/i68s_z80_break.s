        INCLUDE "Ti83p.def"	; ROM / RAM adresses on Ti83+[SE]

        ;; routine assumes that BREAK_COL is 0
_i68s_sys_break_key:
        GLOBAL _i68s_sys_break_key
        bit onInterrupt, (IY + onFlags)
        ld l, 0
        jr z, skip
        ld l, 1
skip:
        res onInterrupt, (IY + onFlags)
        ret
