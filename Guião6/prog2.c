#include <detpic32.h>

void delay(int ms);

int main(void){

volatile int aux;

					
	TRISD = (TRISD & 0xF7FF);	// 1111 0111 1111 1111 define RD11(int4) as output
	
	// configuration sequence
	
	TRISBbits.TRISB4 = 1; 		// RD11 digital output disconnected
	AD1PCFGbits.PCFG4 = 0; 	// RD11 configured as analog input (AN4)
	
	AD1CON1bits.SSRC = 7; 		// Conversion trigger selection bits: in this
					// mode an internal counter ends sampling and
					// starts conversion
					
	AD1CON1bits.CLRASAM = 1; 	// Stop conversions when the 1st A/D converter
					// interrupt is generated. At the same time,
					// hardware clears the ASAM bit
	
	AD1CON3bits.SAMC = 16; 		// Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = 1-1; 	// Interrupt is generated after N samples
					// (replace N by the desired number of
					// consecutive samples)

	AD1CHSbits.CH0SA = 4; 		// replace x by the desired input
					// analog channel (0 to 15)

	AD1CON1bits.ON = 1; 		// Enable A/D converter
					// This must the last command of the A/D
					
	while(1)
	{
	AD1CON1bits.ASAM = 1;		// Start conversion
	
	LATDbits.LATD11 = 1;		 // Set LATD11 (LATD11=1)
	
	while( IFS1bits.AD1IF == 0 );	// Wait while conversion not done (AD1IF == 0)
	
	LATDbits.LATD11 = 0;		// Reset LATD11 (LATD11=0)
	
	aux = ADC1BUF0;			// Read conversion result (ADC1BUF0) to "aux" variable
	
	IFS1bits.AD1IF = 0;		// Reset AD1IF (should be done after reading the conversion result)
	}

return 0;
}

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
