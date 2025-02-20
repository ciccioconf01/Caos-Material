.section .data
v_int:		.word 1,2,3,7,1
n:			.word 5
res:		.word 127

.global _start
_start:

ldr r0,=v_int //vet
ldr r1,=n
ldr r2,[r1] //lenght
ldr r7,=res

bl function

b .

function:
	mov r3,#0 //counter
	mov r4,#0 //max value
	
loop:
	cmp r3, r2
	beq exit_loop
	ldr r5, [r0, r3, LSL #2]
	cmp r4,r5
	bge not_swap
	mov r4,r5
not_swap:
	add r3,r3,#1
	b loop
	
exit_loop:
	mov r1,r4
	str r1, [r7]
	bx lr