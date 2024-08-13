        INCLUDE "Ti83p.def"	; ROM / RAM adresses on Ti83+[SE]
        
_i68s_sys_read_matrix:
        GLOBAL _i68s_sys_read_matrix

        push af                 ; preserve registers
        push hl

        ;; AFAICT this is the easiest way to do this

        REPTI mask, 0b11111110, 0b11111101, 0b11111011, 0b11110111, 0b11101111, 0b11011111, 0b10111111
        
        ;; load
        ld a, mask
        
        ;; do the read
        di
        out (1), a              ; send row mask to port 1
        in a, (1)               ; read key matrix state
        ei

        cpl                     ; invert byte read, might remove this at some point
        
        ld (hl), a              ; load result into array
        inc hl                  ; extraneous on final loop, whatever

        ENDR
        
        ;; wrap up
        pop hl
        pop af
        ret
