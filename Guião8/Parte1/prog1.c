#include <detpic32.h>

int main(void)
{
	// Configure Timer T3 (2 Hz with interrupts disabled)
	T3CONbits.TCKPS = 7; 		// 20000000/((65535+1)*2) = 152 -> 256(7)
	PR3 = 39062; 			// Fout = 20MHz / (256 * (x + 1)) = 2 Hz
	TMR3 = 0; 			// Clear timer T3 count register
	T3CONbits.TON = 1; 		// Enable timer T3 (must be the last command of the timer configuration sequence)
while(1)
{
	while(IFS0bits.T3IF == 0);	// Wait while T3IF = 0
	IFS0bits.T3IF = 0;		// Reset T3IF
	putChar('.');
}
return 0;
}
