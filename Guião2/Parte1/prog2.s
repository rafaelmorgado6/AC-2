.equ READ_CORE_TIMER,11
.equ RESET_CORE_TIMER,12
.equ PUT_CHAR,3
.equ PRINT_INT,6

.data
.text
.globl main

main: 
	addiu $sp,$sp,-16
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	
	
	li $s0,0 			# counter1 = 0
	li $s1,0 			# counter5 = 0
	li $s2,0 			# counter10 = 0
	
while1: 	
	li $a0,1
	jal delay	
	
	addi $s0,$s0,1			# counter1++
	
	li $t2,4
	sll $t2,$t2,16			# 4 << 16
	ori $a1,$t2,10			# 10 | 5 << 16
	
	move $a0,$s0
	la $v0,PRINT_INT
	syscall				# printInt(counter1++, 10 | 4 << 16 )
	
	li $a0,'\r'
	la $v0,PUT_CHAR
	syscall				# putChar('\r')
	
	j while1
	
	li $v0,0		       # return 0
	
	lw $s2,12($sp)
	lw $s1,8($sp)
	lw $s0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,16
	 
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
	move $t5,$a0			# ms
	mul $t6,$t5,$t4			# k * ms
	
	bge $t1,$t6,endwhile2		# readCoreTimer() < K * ms
	
	j while2
endwhile2: 
	
	jr $ra
