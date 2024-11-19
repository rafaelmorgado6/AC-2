#include <detpic32.h>

int main(void)
{
	//config Timer2
	T2CONbits.TCKPS = 2; 	// prescaler=2(2,543->4)
	PR2 = 41666; 		// Fout = 20MHz / (4 * (x + 1)) = 120 Hz
	TMR2 = 0; 		// Clear timer T2 count register
	T2CONbits.TON = 1; 	// Enable timer T2 (must be the last command of the timer configuration sequence)
	
	// config OC2
	OC2CONbits.OCM = 6; 	// PWM mode on OCx; fault pin disabled
	OC2CONbits.OCTSEL =0;	// Use timer T2 as the time base for PWM generation
	OC2RS = 31250; 		// Ton constant
	OC2CONbits.ON = 1; 	// Enable OC1 module

	// config RB2 e RB0
	TRISBbits.TRISB2 = 1;
	TRISBbits.TRISB0 = 1;
	
	
	int a;
	int b;
	
	while(1)
	{
		resetCoreTimer();
		while(readCoreTimer()<20000*0.36);
		
		a = PORTBbits.RB2;
		b = PORTBbits.RB0;
		
		if(a == 0 && b == 0)
			OC2RS = 12500;		// 30%
		if(a == 1 && b == 1)
			OC2RS = 23000;		// 75%
			  
	}

return 0;
}
