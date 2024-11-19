#include <detpic32.h>

volatile unsigned int temp; 

void send2displays(unsigned char value);

unsigned char toBCD(unsigned char value);

int main(void)
{
	// config ADC
	TRISBbits.TRISB4 = 1; 		
	AD1PCFGbits.PCFG4= 0; 		
	AD1CON1bits.SSRC = 7; 		
	AD1CON1bits.CLRASAM = 1; 
	AD1CON3bits.SAMC = 16; 	
	AD1CON2bits.SMPI = 2-1; // 2 amostras
	AD1CHSbits.CH0SA = 4; 	
	AD1CON1bits.ON = 1; 
	
	// config Timer2
	T2CONbits.TCKPS = 2; 	// prescaler=2(2,543->4)
	PR2 = 41665; 		// Fout = 20MHz / (4 * (x + 1)) = 120 Hz
	TMR2 = 0; 		// Clear timer T2 count register
	T2CONbits.TON = 1; 	// Enable timer T2 (must be the last command of the timer configuration sequence)
	
	// config Timer2 interrupts
	IPC2bits.T2IP = 2; 	// Interrupt priority (must be in range [1..6])
	IEC0bits.T2IE = 1; 	// Enable timer T2 interrupts
	IFS0bits.T2IF = 0; 	// Reset timer T2 interrupt flag
	
	EnableInterrupts();
	
	// config dislays
	TRISB = TRISB & 0x80FF;	// 1000 0000 1111 1111
	TRISD = TRISD & 0xFF9F;	// 1111 1111 1001 1111
	
	
	while(1)
	{
		int i;
		int soma = 0;
		int aux;
		int media;
		
		AD1CON1bits.ASAM = 1; // Start conversion
		
		while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done
		
		int *p=(int *)(&ADC1BUF0);
		
		for(i=0;i<16;i++)
		{
			aux = p[i*4];
			soma += aux;
		}
		media = soma / 2;
		
		temp = (media*(65-15)+511)/1023 + 15;
		
		IFS1bits.AD1IF = 0;
		
		resetCoreTimer();
		while(readCoreTimer()<20000*1/10*1000);
		
	}
	
return 0;
}

void _int_(8) isr_T2(void)
{
	send2displays(toBCD(temp));
	
	IFS0bits.T2IF = 0;
}

void send2displays(unsigned char value)
{
static const char display7Scodes[] = {0x3F, 0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6f};
static char displayFlag = 0;

	char digit_low = value & 0x0F;
	char digit_high = value >> 4;

	if(displayFlag == 0){
	LATDbits.LATD5 = 0;			// RD5 = 0, não ativa disply 
	LATDbits.LATD6 = 1;			// RD6 = 1, ativa display
						// select display high	
						// send digit_high (dh) to display
	LATB = (LATB & 0x80FF) | display7Scodes[digit_high] << 8;	// int display= disp7Scodes[dh] << 8;
	}								// LATB = LATB & 0x80FF;
									// LATB = LATB | display;
	else
	{
	LATDbits.LATD6 = 0;			// RD6 = 0, não ativa display
	LATDbits.LATD5 = 1;			// RD5 = 1, ativa disply 
						// select display low				
						// send digit_low (dl) to display 0x0F
	
	LATB = (LATB & 0x80FF) | display7Scodes[digit_low] << 8;
	}
	displayFlag = !displayFlag;
	
	return 0;
}

unsigned char toBCD(unsigned char value)
{
	return((value/10)<<4)+(value%10);
}

