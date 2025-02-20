.global _start
_start:

	mov r0,#1 //index
    mov r1,#0 //accumulator

loop:
    add r1,r1,r0
    add r0,r0,#1
    cmp r0,#31
    bne loop

end:
    b .