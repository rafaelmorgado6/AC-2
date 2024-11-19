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
	AD1CON2bits.SMPI = 2-1;		// 2 amostras
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1;
	
	// config Timer3
	T3CONbits.TCKPS = 2; 	// prescaler=2(2,179->4)
	PR3 = 35714; 		// Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
	TMR3 = 0; 		// Clear timer T3 count register
	T3CONbits.TON = 1; 	// Enable timer T3 (must be the last command of the timer configuration sequence)

	// config interrupts
	IPC3bits.T3IP = 2; 	// Interrupt priority (must be in range [1..6])
	IEC0bits.T3IE = 1; 	// Enable timer T2 interrupts
	IFS0bits.T3IF = 0; 	// Reset timer T2 interrupt flag
	
	EnableInterrupts();
	
	// config displays
	TRISB = TRISB & 0x80FF;
	TRISD = TRISD & 0xFF9F;
	
	while(1)
	{
	int i;
	int soma=0;
	int aux;
	int media;
	
	AD1CON1bits.ASAM = 1; 	// Start conversion
	
	while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done
	
	int *p = (int *)(&ADC1BUF0);
	
	for(i=0; i<16; i++)
	{
		aux = p[i*4];
		soma += aux;
	} 
	media = soma/2;
	
	temp = (media*(75-10)+511)/1023 + 10;
	
	soma = 0;
	media = 0;
	
	IFS1bits.AD1IF = 0;
	
	resetCoreTimer();
	while(readCoreTimer()<20000*1/5*1000);
	}
return 0;
}

void send2displays(unsigned char value)
{
static const char display7Scodes[] = {0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
unsigned char dh, dl;
static char displayFlag = 0;
	
	if(displayFlag == 0){
// select display high
	LATDbits.LATD6 = 1;
	LATDbits.LATD5 = 0;	
// send digit_high (dh) to display: dh = value >> 4
	dh = value >> 4;
	LATB = (LATB & 0x80FF ) | display7Scodes[dh] << 8;
	}else{	
// select display low
	LATDbits.LATD6 = 0;
	LATDbits.LATD5 = 1;
// send digit_low (dl) to display: dl = value & 0x0F
	dl = value & 0x0F;
	LATB = (LATB & 0x80FF ) | display7Scodes[dl] << 8;
	}
	
	displayFlag = !displayFlag;

}

unsigned char toBCD(unsigned char value)
{
	return((value/10)<<4)+(value%10);
}

void _int_(12) isr_T3(void)
{
	send2displays(toBCD(temp));

	IFS0bits.T3IF = 0;
}




