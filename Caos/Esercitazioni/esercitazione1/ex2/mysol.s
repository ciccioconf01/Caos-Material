.section .data
	array:     .word 1,2,3,4,5  //lenght=5 and sum=15
	
	.section .text
	.global _start

_start:
	ldr r0, =array  //address of array
	mov r2,#5  //lenght of array
	
	bl sum_array
	
	b end
	
@function: sum_array
@argument:
@	r0
@	r2
@return:
@	r3
	
	
sum_array:
	
	mov r1,#0  //actual index
	mov r3,#0  //accumulator
	mov r4,#0  //tmp

loop:
	cmp r1,r2
	beq end_loop
	ldr r4, [r0,r1, lsl #2]
	add r3,r3,r4
	add r1,r1,#1
	b loop
	
end_loop:
	bx lr

end:
	b .