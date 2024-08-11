	INCLUDE "Ti83p.def"	; ROM / RAM adresses on Ti83+[SE]

_send_byte:
        GLOBAL _send_byte

        ld a, l
        INVOKE _SendAByte
        ret


_recv_byte:
        GLOBAL _recv_byte

        INVOKE _RecAByteIO
        ld l, a
        ret
