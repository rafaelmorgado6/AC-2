.equ READ_CORE_TIMER,11
.equ RESET_CORE_TIMER,12
.equ PUT_CHAR,3
.equ PRINT_INT,6
.equ PRINT_STRING,8
.equ inkey,1
.data
str:	 .asciiz "   "
.text
.globl main

main: 
	addiu $sp,$sp,-24
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s3,16($sp)
	sw $s4,20($sp)
	
	
	li $s0,0 			# counter1 = 0
	li $s1,0 			# counter5 = 0
	li $s2,0 			# counter10 = 0
	li $s4,1000			# ms = 1000 (incrementos de 1s)
	
while1: 
	la $v0,inkey
	syscall			# inkey();
	move $s3,$v0		# $s3 = inkey();


if1:
	bne $s3,'a',if2
	li $s4,500
	j endif1
if2:
	bne $s3,'n',if3	
	li $s4,1000
	j endif1

if3:
	bne $s3,'r',if4
	sub $s0,$s0,$s0
	sub $s1,$s1,$s1
	sub $s2,$s2,$s2
	j endif1

if4:	
	bne $s3,'s',endif1
if5:
	la $v0,inkey
	syscall			# inkey();
	move $s3,$v0		# $s3 = inkey();
	beq $s3,'n',if2
	beq $s3,'a',if1
	beq $s3,'r',if3		
	j if5
	
endif1:
	move $a0,$s4
	jal delay	
	
	addi $s0,$s0,1			# counter1++
	
	rem $t7,$s0,2
	bne $t7,0,catorze
	addi $s1,$s1,1			# counter5++
catorze:
	rem $t8,$s0,10
	bne $t8,0,islide
	addi $s2,$s2,1			# counter10++
islide:
	
	
	li $t2,4
	sll $t2,$t2,16			# 4 << 16
	ori $a1,$t2,10			# 10 | 5 << 16
	
	move $a0,$s0
	la $v0,PRINT_INT
	syscall				# printInt(counter1++, 10 | 4 << 16 )
	
	la $a0,str
	li $v0,PRINT_STRING
	syscall				# space
	
	move $a0,$s1
	la $v0,PRINT_INT
	syscall				# printInt(counter5++, 10 | 4 << 16 )
	
	la $a0,str
	li $v0,PRINT_STRING
	syscall				# space
	
	move $a0,$s2
	la $v0,PRINT_INT
	syscall				# printInt(counter10++, 10 | 4 << 16 )
	
	li $a0,'\r'
	la $v0,PUT_CHAR
	syscall				# putChar('\r')
	
	j while1
	
	li $v0,0		       # return 0
	
	lw $s4,20($sp)
	lw $s3,16($sp)
	lw $s2,12($sp)
	lw $s1,8($sp)
	lw $s0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,24
	 
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
