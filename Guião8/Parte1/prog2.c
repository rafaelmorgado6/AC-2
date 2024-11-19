#include <detpic32.h>

int main(void)
{
	// Configure Timer T3 (2 Hz with interrupts disabled)
	T3CONbits.TCKPS = 7; 		// 1:256 prescaler (i.e. fout_presc = 78125 Hz)
	PR3 = 39062; 			// Fout = 20MHz / (256 * (x + 1)) = 2 Hz
	TMR3 = 0; 			// Clear timer T3 count register
	IPC3bits.T3IP = 2; 		// Interrupt priority (must be in range [1..6])
	IEC0bits.T3IE = 1; 		// Enable timer T2 interrupts
	IFS0bits.T3IF = 0; 		// Reset timer T2 interrupt flag
	T3CONbits.TON = 1; 		// Enable timer T3 (must be the last command of the timer configuration sequence)

	EnableInterrupts();
while(1)
{
}
return 0;
}

void _int_(12) isr_T3(void) 		// Replace VECTOR by the timer T3 vector number
{
	putChar('.');
	IFS0bits.T3IF = 0;      	// Reset T3 interrupt flag
}
