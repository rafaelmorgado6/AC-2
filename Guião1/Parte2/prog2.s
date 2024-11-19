# int main(void)
# {
# char c;
# do
# {
# 	c = getChar();
# 	putChar( c );
# } while( c != '\n' );
# 	return 0;
# }
	
	.data
	.equ getChar,2
	.equ putChar,3
	.text
	.globl main
main: 
do:
	la $v0,getChar
	syscall			# getChar();
	move $t0,$v0		# c = getChar();
	
	add $t1,$t0,1		# c+1
	
	move $a0,$t1     
	la $v0,putChar		# putChar()
	syscall                 # putChar(c+1)
	
while:
	bne $t0,'\n',do		# while( c != '\n' )
	
	jr $ra
	
	
	
	
	
