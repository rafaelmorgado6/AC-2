#include <detpic32.h>

void delay(int ms);

int main(void){
	
	TRISBbits.TRISB4 = 1; 		// RB4 digital output disconnected
	AD1PCFGbits.PCFG4 = 0; 		// RB4 configured as analog input (AN4)
	
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
					// configuration sequence
	
	while(1)
	{
	AD1CON1bits.ASAM = 1;		// Start conversion
	
	while( IFS1bits.AD1IF == 0 );	// Wait while conversion not done (AD1IF == 0)
	
	int i;
	
	//ACESSO AS 16 POSIÇOES DO BUFFER
	
	int *p = (int *)(&ADC1BUF0);
	for( i = 0; i < 16; i++ ) {
	printInt( p[i*4], 10 | 4 << 16);
	printf(" ");
	
	}
	putChar('\n');
	
	IFS1bits.AD1IF = 0;	// Reset
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

