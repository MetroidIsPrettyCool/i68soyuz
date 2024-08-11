        INCLUDE "Ti83p.def"	; ROM / RAM adresses on Ti83+[SE]

        ;; routine assumes that BREAK_COL is 0
_i68s_sys_break_key:
        GLOBAL _i68s_sys_break_key
        ld l, (IY + onFlags)    ; insofar as I can tell, onInterrupt is the only field of onFLags
        ld (IY + onFlags), 0
        ret
