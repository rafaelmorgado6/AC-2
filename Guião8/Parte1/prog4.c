#include <detpic32.h>

volatile int count = 0;
int main(void)
{
	// Configure Timer T1(A) (5 Hz with interrupts enabled)
	T1CONbits.TCKPS = 2; 		// 20000000/((65535+1)*5) = 61 -> 16(2)
	PR1 = 62499; 			// Fout = 20MHz / (64 * (x + 1)) = 5 Hz
	TMR1 = 0; 			// Clear timer T1 count register
	IPC1bits.T1IP = 2; 		// Interrupt priority (must be in range [1..6])
	IEC0bits.T1IE = 1; 		// Enable timer T1 interrupts
	IFS0bits.T1IF = 0; 		// Reset timer T1 interrupt flag
	T1CONbits.TON = 1; 		// Enable timer T1 (must be the last command of the timer configuration sequence)

	// Configure Timer T3(B) (25 Hz with interrupts enabled)
	T3CONbits.TCKPS = 4; 		// 20000000/((65535+1)*25) = 13 -> 16(4)
	PR3 = 49999; 			// Fout = 20MHz / (16 * (x + 1)) = 25 Hz
	TMR3 = 0; 			// Clear timer T3 count register
	IPC3bits.T3IP = 2; 		// Interrupt priority (must be in range [1..6])
	IEC0bits.T3IE = 1; 		// Enable timer T3 interrupts
	IFS0bits.T3IF = 0; 		// Reset timer T3 interrupt flag
	T3CONbits.TON = 1; 		// Enable timer T3 (must be the last command of the timer configuration sequence)
	
	EnableInterrupts();
while(1)
{
}
return 0;
}

void _int_(4) isr_T1(void)
{
	putChar('1');
		
	IFS0bits.T1IF = 0;      	// Reset T3 interrupt flag
}

void _int_(12) isr_T3(void) 		// Replace VECTOR by the timer T3 vector number
{
	putChar('3');
		
	IFS0bits.T3IF = 0;      	// Reset T3 interrupt flag
}
