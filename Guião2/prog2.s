.equ READ_CORE_TIMER,11
.equ RESET_CORE_TIMER,12
.equ PUT_CHAR,3
.equ PRINT_INT,6
.data
.text
.globl main

main: 
	addiu $sp,$sp,-8
	sw $ra,0($sp)
	sw $s0,4($sp)
	
	li $s0,0 			# counter = 0
	
while1: 	
	
	jal delay	
	
	addi $s0,$s0,1			# counter++
	
	li $t2,4
	sll $t2,$t2,16			# 4 << 16
	ori $a1,$t2,10			# 10 | 5 << 16
	
	move $a0,$s0
	la $v0,PRINT_INT
	syscall				# printInt(counter++, 10 | 4 << 16 )
	
	li $a0,'\r'
	la $v0,PUT_CHAR
	syscall				# putChar('\r')
	
	j while1
	
	li $v0,0		       # return 0
	
	lw $s0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,8
	 
	jr $ra 
	
#################################################################################################
# 1000ms - 20000000HZ
# 1ms    - (k) 20000HZ 

delay:
	li $v0,RESET_CORE_TIMER 
	syscall 			# resetCoreTimer()
while2:	
	li $v0,READ_CORE_TIMER 
	syscall 			# readCoreTimer()
	move $t1,$v0
	
	li $t4,20000			# k = 20000
	li $t5,1000			# ms = 1
	mul $t6,$t5,$t4			# k * ms
	
	bge $t1,$t6,endwhile2		# readCoreTimer() < K * ms
	
	j while2
endwhile2: 
	
	jr $ra
	
