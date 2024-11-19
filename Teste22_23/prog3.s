	.data
	.equ SFR_BASE_HI, 0xBF88
	.equ TRISE, 0x6100
	.equ LATE, 0x6120
	.equ readCoreTimer, 11
	.equ resetCoreTimer, 12
	.equ printInt,6
	.equ putChar, 3
	.text
	.globl main
main:
	lui $t0,SFR_BASE_HI
	
	#config bits
	lw $t1,TRISE($t0)
	andi $t1,$t1,0xFF83
	sw $t1,TRISE($t0)
	
	#config saidas
	lw $t1,LATE($t0)
	andi $t1,$t1,0xFF83	# da reset
	ori $t1,$t1,0x0004	# ligar RE2	0000 0000 000 0100
	sw $t1,LATE($t0)
	
	li $t2,1	# valor inicial 00001
	
	move $a0,$t2	# $t2 -> $a0
	li $a1,5	# $a1 = 5
	sll $a1,$a1,16	# 5 << 16
	ori $a1,$a1,2	# 2 \ 5 << 15
	li $v0,printInt
	syscall
	
	# delay
	li $t5,20000
	mul $t5,$t5,435		# delay(435)

while:
	li $a0,'\n'
	li $v0,putChar
	syscall
	
	li $v0,resetCoreTimer
	syscall
delay:
	li $v0,readCoreTimer
	syscall
	
	blt $v0,$t5,delay
enddelay:
	
	sll $t2,$t2,1		# fazer a sequencia
	
if:
	bne $t2,0x0020,endif	# if(sequencia = 0000 0000 0010 0000)
	
	li $t2,1
endif:

	lw $t1,LATE($t0)
	andi $t1,$t1,0xFF83	# dar reset saida
	sll $t3,$t2,2		# por nos bits de saida
	or $t1,$t1,$t3
	sw $t1,LATE($t0)
	li $v0,printInt
	syscall
	
	j while
endwhile:
	li $v0,0
	
	jr $ra
	
	
	
	
	
