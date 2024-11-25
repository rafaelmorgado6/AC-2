#include <detpic32.h>

int main(void)
{

// Configure Timer T3(B) (100 Hz with interrupts enabled)
	T3CONbits.TCKPS = 2; 		// 20000000/((65535+1)*100) = 3.05 -> 4(2)
	PR3 = 49999; 			// Fout = 20MHz / (2 * (x + 1)) = 100 Hz
	TMR3 = 0; 			// Clear timer T3 count register
	IPC3bits.T3IP = 2; 		// Interrupt priority (must be in range [1..6])
	IEC0bits.T3IE = 1; 		// Enable timer T3 interrupts
	IFS0bits.T3IF = 0; 		// Reset timer T3 interrupt flag
	T3CONbits.TON = 1; 		// Enable timer T3 (must be the last command of the timer configuration sequenc

	OC1CONbits.OCM = 6; 		// PWM mode on OCx; fault pin disabled
	OC1CONbits.OCTSEL =0;		// Use timer T2 as the time base for PWM generation
	OC1RS = 12500; 			// Ton constant
	OC1CONbits.ON = 1; 		// Enable OC1 module

	EnableInterrupts();            // Global Interrupt Enable
	
while(1);
return 0;
}

void _int_(12)  isr_T3()
{
	IFS0bits.T3IF = 0;
}

