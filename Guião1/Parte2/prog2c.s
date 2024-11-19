# int main(void)
# {
# int value;
# while(1)
# {
# printStr("\nIntroduza um inteiro (sinal e módulo): ");
# value = readInt10();
# printStr("\nValor em base 10 (signed): ");
# printInt10(value);
# printStr("\nValor em base 2: ");
# printInt(value, 2);
# printStr("\nValor em base 16: ");
# printInt(value, 16);
# printStr("\nValor em base 10 (unsigned): ");
# printInt(value, 10);
# printStr("\nValor em base 10 (unsigned), formatado: ");
# printInt(value, 10 | 5 << 16); // ver nota de rodapé 3
# }
# return 0;
# }

	.data
	.equ printStr,8
	.equ printInt10,7
	.equ printInt,6
	.equ readInt,4
str1:	.asciiz "\nIntroduza um inteiro (sinal e módulo): "
str2:	.asciiz "\nValor em base 10 (signed): "
str3:	.asciiz "\nValor em base 2: "
str4:	.asciiz "\nValor em base 4: "
str5:	.asciiz "\nValor em base 10 (unsigned): "
str6:	.asciiz "\nValor em base 10 (unsigned), formatado: "
	.text
	.globl main
main: 
while:
	la $a0,str1
	li $v0,printStr
	syscall			# printStr( str1 )
	
	la $v0,readInt
	syscall			# readInt()
	move $t0,$v0		# value = readInt()
	
	la $a0,str2
	li $v0,printStr
	syscall			# printStr( str2 )
	
	move $a0,$t0
	la $v0,printInt10
	syscall			# printInt10( value )
	
	la $a0,str3
	li $v0,printStr
	syscall			# printStr( str3 )
	
	li	$v0, printInt
	move	$a0, $t0
	li	$a1, 2		# valor em base 2
	syscall	
	
	la $a0,str4
	li $v0,printStr
	syscall			# printStr( str4 )
	
	li	$v0, printInt
	move	$a0, $t0
	li	$a1, 16		# valor em base 16
	syscall	
	
	la $a0,str5
	li $v0,printStr
	syscall			# printStr( str5 )
	
	li	$v0, printInt
	move	$a0, $t0
	li	$a1, 10		# valor em base 10 (unsigned)
	syscall	
	
	la $a0,str6
	li $v0,printStr
	syscall			# printStr( str6 )
	
	li $t1,5
	sll $t1,$t1,16		# 5 << 16
	ori $a1,$t1,10		# 10 | 5 << 16
	
	move $a0,$t0
	li $v0,printInt
	syscall			# printInt(value, 10 | 5 << 16 )
	
	j while
endwhile:
	li $v0,0		# return 0
	jr $ra
	
	
