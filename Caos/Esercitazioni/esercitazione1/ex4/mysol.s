.section .text
.global _start

_start:
	mov r1,#10 //lenght of fibonacci series
	mov r2, #1 //first number
	mov r3, #1 //second number
	mov r4, #2 //index
	
	bl fibonacci
	
	b end
	

fibonacci:
	mov r5,#0 //accumulator
	add r5,r2,r3

loop:

	cmp r4, r1
	beq end_loop
	
	add r6,r2,r3 //next number
	add r5,r5,r6
	add r4,r4,#1
	mov r2, r3
	mov r3, r6
	b loop
	
end_loop:
	bx lr
	
end:
	b .
	