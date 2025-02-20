.section .data
num: .word 0xF0F0F0F0

.section .text
.global _start

_start:
	ldr r0, =num //load of number
	mov r1, #32 //lenght of number
	
	bl count_set_bits
	
	b end
	
count_set_bits:
	mov r2,#0 //counter of loops
	mov r3,#0 //counter of set bits
	ldr r4, [r0,r2,lsl #0]
	
loop:
	cmp r2,r1
	beq end_loop
	
	tst r4,#1 //compare least significant bit with 1
	beq count
	b no_count
	
count:
	add r3,r3,#1

no_count:
	add r2,r2,#1
	lsr r4, r4, #1
	b loop
	
	
end_loop:
	bx lr
	
end:
	b .