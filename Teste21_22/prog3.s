
	.data
	.equ SFR_BASE_HI, 0xBF88
	.equ TRISE, 0X6100
	.equ LATE, 0x6120
	.equ readCoreTimer, 11
	.equ resetCoreTimer, 12
	.equ printInt, 6
	.equ putChar, 3
	.text
	.globl main
main:
	lui $t0,SFR_BASE_HI		# $t1=0xBF880000
	
	# config bits
	lw $t1,LATE($t0)
	andi $t1,$t1,0xFFE1		#reset saida	1111 1111 1110 0001
	ori $t1,$t1,0x0012		# 0000 0000 0001 0010
	sw $t1,LATE($t0)
	
	li $t2,0x0009			# valor inicia -> 0000 0000 0000 1001
	
	li $t5,1
	mul $t5,$t5,20000000		# $t5 = 20000000
	divu $t5,$t5,7			# $t5 = 20000000/f, em c era 20000*ms -> 20000*1000/f
while:
	li $v0,resetCoreTimer
	syscall
delay:
	li $v0,readCoreTimer
	syscall
	
	blt $v0,$t5,delay		# se readCoreTimer<$t5 -> jump delay
enddelay:

	lw $t1,LATE($t0)
	andi $t1,$t1,0xFFE1		# reset saida
	
	xori $t2,$t2,0x000F		# $t2 xori 0000 0000 0000 1111		10001 -> 0110
	
	move $a0,$t2
	li $a1,4
	sll $a1,$a1,16			# 4 << 16
	ori $a1,$a1,2			# 2 | 4 << 16
	
	li $v0,printInt
	syscall
	
	sll $t3,$t2,1			# passar do bit0 para o bit1
	or $t1,$t1,$t3
	
	lw $t1,LATE($t0)		# escrever na saida
	
	li $a0,'\n'
	li $v0,putChar
	syscall 			# putChar('\n')
	
	j while
endwhile:
	li $v0,0
	
	jr $ra
