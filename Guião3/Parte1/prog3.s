# TRISx	  -    configurar os portos como entrada ou saída
# LATx    -    escrever um valor num porto configurado como saída
# PORTx   -    ler o valor de um porto configurado como entrada

.data
.equ SFR_BASE_HI, 0xBF88 		# 16 MSbits of SFR area
.equ TRISE, 0x6100 			# TRISE address is 0xBF886100
.equ PORTE, 0x6110			# PORTE address is 0xBF886110
.equ LATE, 0x6120 			# LATE address is 0xBF886120
.equ TRISB, 0x6040 			
.equ PORTB, 0x6050			
.equ LATB, 0x6060
.equ TRISD, 0x60C0 			
.equ PORTD, 0x60D0			
.equ LATD, 0x60E0
.text
.globl main
main:
	lui $t1,SFR_BASE_HI		# $t1=0xBF880000
	
	lw $t2,TRISD($t1)
	ori $t2,$t2,0x0100		# bit 8 a 1 (0000 0001 0000 0000)		
	sw $t2,TRISD($t1)		# RD8 = 1 (input)
	
	lw $t2,TRISE($t1)
	andi $t2,$t2,0xFFFE
	sw $t2,TRISE($t1)		# RE0 = 0 (output)
while:
	lw $t2,PORTD($t1)		# ler valor da entrada
	andi $t2,$t2,0x0100		# reset todos os bits exceto o bit8
	srl $t2,$t2,8			# empurra o bit 8 para a posição do bit 0
	#xori $t2,$t2,0x0001		# nega o bit0
	
	lw $t3,LATE($t1)		# abrir a saida
	andi $t3,$t3,0xFFFE		# reset bit0
	
	or $t3,$t3,$t2
	sw $t3,LATE($t1)		# escrever na saida
	
	j while
	
	jr $ra
	
