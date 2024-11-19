# int main(void)
# {
# char c;
# do {
# c = inkey();
# if( c != 0 )
# putChar( c );
# else
# putChar('.');
# } while( c != '\n' );
# return 0;
# }

	.data
	.equ inkey,1
	.equ putChar,3
	.text
	.globl main
main: 
do:
	la $v0,inkey
	syscall			# inkey();
	move $t0,$v0		# c = inkey();
if:
	beq $t0,0,else
	
	
	move $a0,$t0     
	la $v0,putChar		# putChar()
	syscall                 # putChar(c)
	j while
else:
	li $a0,'.'     
	la $v0,putChar		# putChar()
	syscall                 # putChar('.')
	
while:
	bne $t0,'\n',do		# while( c != '\n' )
	
	jr $ra
