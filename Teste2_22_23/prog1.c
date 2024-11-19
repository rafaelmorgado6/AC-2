#include <detpic32.h>

int main(void)
{

	//config Timer2
	T2CONbits.TCKPS = 2; 	// prescaler=2(2,023->4)
	PR2 = 33332; 		// Fout = 20MHz / (4 * (x + 1)) = 150 Hz
	TMR2 = 0; 		// Clear timer T2 count register
	T2CONbits.TON = 1; 	// Enable timer T2 (must be the last command of the timer configuration sequence)
	
	//config OC2
	OC2CONbits.OCM = 6; 	// PWM mode on OCx; fault pin disabled
	OC2CONbits.OCTSEL =0;	// Use timer T2 as the time base for PWM generation
	OC2RS = 8350; 		// Ton constant
	OC2CONbits.ON = 1; 	// Enable OC1 module

	//config switches
	TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB3 = 1;

	int c;
	int d;
	
	while(1)
	{
		resetCoreTimer();
		while(readCoreTimer()<20000*0.25);
		
		c = PORTBbits.RB0;
		d = PORTBbits.RB3;	// armazenar em c e d o valor das entradas
		
		if( c==1 && d==0)
		{
			OC2RS = 8350;	// 25%
		}
		if(c==0 && d==1)	// 70%
		{
			OC2RS = 23350;
		}
		
	}
return 0;
}
