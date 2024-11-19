#include <detpic32.h>

int main(void)
{
	TRISB = (TRISB & 0x80FF);		// 1000 0000 1111 1111
	TRISD = (TRISD & 0xFF9F);		// 1111 1111 1001 1111
	
	LATDbits.LATD5 = 1;			// RD5 = 1, ativa disply 
	LATDbits.LATD6 = 0;			// RD6 = 0, não ativa display
	LATB = (LATB & 0x0000);
while(1){
	
	char ch;
	ch = getChar();
	if( ch == 'a')
		LATB = (LATB & 0x80FF) | 0xF7FF;	//1111 0111 1111 1111 
	if( ch == 'b')
		LATB = (LATB & 0x80FF) | 0xFCFF;	//1111 1100 1111 1111 
	if( ch == 'c')
		LATB = (LATB & 0x80FF) | 0xB9FF;	//1011 1001 1111 1111 
	if( ch == 'd')
		LATB = (LATB & 0x80FF) | 0xDEFF;	//1101 1110 1111 1111 
	if( ch == 'e')
		LATB = (LATB & 0x80FF) | 0xF9FF;	//1111 1001 1111 1111 
	if( ch == 'f')
		LATB = (LATB & 0x80FF) | 0xF1FF;	//1111 0001 1111 1111 
	if( ch == 'g')
		LATB = (LATB & 0x80FF) | 0xEFFF;	//1110 1111 1111 1111 
}
	
return 0;
}
