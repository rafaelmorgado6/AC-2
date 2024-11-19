.equ READ_CORE_TIMER,11
.equ RESET_CORE_TIMER,12
.equ PUT_CHAR,3
.equ PRINT_INT,6
.data
.text
.globl main

main: 
	li $t0,0 			# counter = 0
while1: 
	li $v0,RESET_CORE_TIMER 
	syscall 			# resetCoreTimer()

while2:
	li $v0,READ_CORE_TIMER 
	syscall 			# readCoreTimer()
	move $t1,$v0
	
	bge $t1,20000000,endwhile2
	j while2
endwhile2:	
	addi $t0,$t0,1			# counter++
	
	li $t2,4
	sll $t2,$t2,16			# 4 << 16
	ori $a1,$t2,10			# 10 | 5 << 16
	
	move $a0,$t0
	la $v0,PRINT_INT
	syscall				# printInt(counter++, 10 | 4 << 16 )
	
	li $a0,'\r'
	la $v0,PUT_CHAR
	syscall				# putChar('\r')
	
	j while1
	
	li $v0,0		       # return 0
	jr $ra 
