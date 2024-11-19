.data
	.equ SFR_BASE_HI, 0xBF88
	.equ TRISE, 0x6100
	.equ TRISB, 0x6040
	.equ PORTB, 0x6050
	.equ LATE, 0x6120
	.equ redCoreTimer, 11
 	.equ resetCoreTimer, 12
 	.text
 	.globl main
 main:
 	addiu $sp,$sp,-12
 	sw $ra,0($sp)
 	sw $s0,4($sp)
 	sw $s1,8($sp)
 	
 	lui $s0,SFR_BASE_HI
 	
 # SAIDAS RE4-RE1:
 	lw $t1,TRISE($s0)
 	andi $t1,$t1,0xFFE1
 	sw $t1,TRISE($s0)
 	
 # ENTRADAS RB3-RB1:
 	lw $t1,TRISB($s0)
 	ori $t1,$t1,0x000E
 	sw $t1,TRISB($s0)
 	
 	li $s1,0
 
 while:
 	lw $t1,LATE($s0)	# ler saida
 	andi $t1,$t1,0xFFE1	# reset
 	
 	or $t1,$t1,$s1		# colocar variavel de contagem na saida
 	sll $t1,$t1,1		# RB3-RB1 -> RB2-RB0
 	sw $t1,LATE($s0)	# atualizar saida
 	
 	li $a0,666		# f = 1.5HZ = 666ms
 	jal delay
 	
 	andi $t5,$s1,0x0008	# $t5 terá o bit +sig a 0 ou a 1 dependendode $s1
 if:
 	bge $t5,8,else		# se bit sig for =1 ou seja maior que 8 salta se for =0 (menor que 8) faz
 	sll $s1,$s1,1		# deslocamento 
 	ori $s1,$s1,0x0001	#introduçao do bit 1
 	
 	j endif
 else:
 	sll $s1,$s1,1		#deslocamento, nao se precisa de meter a introduçao do bit pois é unsigned este deslocamento
 endif:	
 	j while
 endwhile:
 	li $v0,0
 	
 	lw $ra,0($sp)	
	lw $s0,4($sp)
	lw $s1,8($sp)
	addiu $sp,$sp,12
	
	jr $ra
	
########################################################################################################

delay:
	li $v0,resetCoreTimer
	syscall
	
	mul $t0,$a0,20000	# $t0=k*ms
while1:
	li $v0,readCoreTimer
	syscall
	
	bge $v0,$t0,endwhile1	# readCoreTimer < K*ms
	j while1
endwhile1:
	jr $ra
