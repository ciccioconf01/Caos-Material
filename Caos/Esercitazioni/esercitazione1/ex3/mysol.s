
.section .data
	array: .word 1,2,3,4,5
	
	.section .text
	.global _start
	
_start:
	ldr r0, =array //address of array
	mov r1, #5 //lenght of array
	lsr r2, r1, #1
	
	bl reverse_array
	
	bl control
	
	b end


reverse_array:
	mov r3, #0 //first index
	mov r4, #4 //last index
	
loop:
	cmp r2,r3
	beq end_loop
	ldr r5, [r0,r3,lsl #2] 
	ldr r6, [r0,r4,lsl #2]
	str r5, [r0,r4,lsl #2]
	str r6, [r0,r3,lsl #2]
	
	add r3, r3, #1
	sub r4, r4, #1
	
	b loop
	
end_loop:
	bx lr


control: 
	mov r3, #0 //index
	
loop2:
	cmp r3,r1
	beq end_loop2
	ldr r10, [r0, r3, lsl #2]
	add r3, r3, #1
	b loop2

end_loop2:
	bx lr
	
end:
	b .