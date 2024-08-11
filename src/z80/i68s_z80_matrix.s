        ;; TODO: Get rid of this stupid left shift loop and hard code it all to write into an array

        INCLUDE "Ti83p.def"	; ROM / RAM adresses on Ti83+[SE]

_i68s_sys_read_matrix:
        GLOBAL _i68s_sys_read_matrix

        push af                 ; preserve af register pair

        ;; a = ~(1 << )l
        ld a, 1
        inc l                   ; since l might be zero, and it's easiest to test for 0
        or a                    ; clear carry
loop:
        dec l
        jr z, done
        rla
        jr loop
done:
        cpl

        ;; do the read
        di
        out (1), a              ; send row mask to port 1
        in a, (1)               ; read key matrix state
        ei

        ;; wrap up
        cpl                     ; negate the result
        ld l, a                 ; copy result into l register (return value)
        pop af                  ; restore af register pair
        ret
