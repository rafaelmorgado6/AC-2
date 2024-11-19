#include <detpic32.h>

unsigned char toBcd(unsigned char);
void send2displays(unsigned char);

static volatile int V=0;

int main(void)
{
//----------------------------------TIMERS-------------------------------------------------------------
	// Configure Timer T1(A) (5 Hz with interrupts enabled)
	T1CONbits.TCKPS = 2; 		// 20000000/((65535+1)*5) = 61 -> 16(2)
	PR1 = 62499; 			// Fout = 20MHz / (64 * (x + 1)) = 5 Hz
	TMR1 = 0; 			// Clear timer T1 count register
	IPC1bits.T1IP = 2; 		// Interrupt priority (must be in range [1..6])
	IEC0bits.T1IE = 1; 		// Enable timer T1 interrupts
	IFS0bits.T1IF = 0; 		// Reset timer T1 interrupt flag
	T1CONbits.TON = 1; 		// Enable timer T1 (must be the last command of the timer configuration sequence)

	// Configure Timer T3(B) (100 Hz with interrupts enabled)
	T3CONbits.TCKPS = 2; 		// 20000000/((65535+1)*100) = 3.05 -> 4(2)
	PR3 = 49999; 			// Fout = 20MHz / (2 * (x + 1)) = 100 Hz
	TMR3 = 0; 			// Clear timer T3 count register
	IPC3bits.T3IP = 2; 		// Interrupt priority (must be in range [1..6])
	IEC0bits.T3IE = 1; 		// Enable timer T3 interrupts
	IFS0bits.T3IF = 0; 		// Reset timer T3 interrupt flag
	T3CONbits.TON = 1; 		// Enable timer T3 (must be the last command of the timer configuration sequence)
			
	
//----------------------------------ADC---------------------------------------------------------------	
	
	TRISBbits.TRISB4 = 1; // RBx digital output disconnected
	AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
	AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
	// mode an internal counter ends sampling and starts conversion
	AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
	// interrupt is generated. At the same time,hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = 8-1; //N-1 Interrupt is generated after N samples
	// (replace N by the desired number of consecutive samples)
	AD1CHSbits.CH0SA = 4; // replace x by the desired input
	// analog channel (0 to 15)
	AD1CON1bits.ON = 1; // Enable A/D converter
	// This must the last command of the A/D
	// configuration sequence
	
	
	TRISB = (TRISB & 0x80FF); //1000 0000 1111 1111 -> bits RB14-8 definidos como saida
	TRISD = (TRISD & 0xFF9F); //1111 1111 1001 1111 bits RD5-6 output
	
	IPC6bits.AD1IP = 2; // configure priority of A/D interrupts
	IFS1bits.AD1IF = 0; // clear A/D interrupt flag
	IEC1bits.AD1IE = 1; // enable A/D interrupts
	EnableInterrupts();
while(1)

{
}
		
return 0;
}

unsigned char toBcd(unsigned char value)
{
return ((value / 10) << 4) + (value % 10);
}


void send2displays(unsigned char value)
{
static const char display7Scoder[] = {0x3F, 0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6f,0x77,0x7C,0x39,0x5E,0x79,0x71};
static char displayFlag = 0;

	if(displayFlag == 0)
	{
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;
		
		char digit_high = value >> 4;
		LATB = (LATB & 0x80FF) | display7Scoder[digit_high] << 8;
	}
	else
	{
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;
		
		char digit_low = value & 0x0F;
		LATB = (LATB & 0x80FF) | display7Scoder[digit_low] << 8;
	}
	displayFlag = !displayFlag;
}

void _int_(4) isr_T1(void)
{
	AD1CON1bits.ASAM = 1;    		 // Start conversion
		
	IFS0bits.T1IF = 0;      	// Reset T3 interrupt flag
}

void _int_(12) isr_T3(void) 		// Replace VECTOR by the timer T3 vector number
{
	send2displays(V);		// Send voltage value to displays
		
	IFS0bits.T3IF = 0;      	// Reset T3 interrupt flag
}

void _int_(27) isr_adc()
{
	int i, soma, aux, media;
	
	while( IFS1bits.AD1IF == 0 );		// Wait while conversion not done (AD1IF == 0)

	putChar('\r');
	int *p = (int *)(&ADC1BUF0);
	soma = 0;

	for( i = 0; i < 16; i++ ) {		// Convert analog input (4 samples)
	
		aux = p[i*4];
		
		soma += aux;
	}

	media = soma/8;

	V = (media*33+511)/1023;
	printInt10(V);
	V = toBcd(V); 
	
	soma = 0;
	media = 0;
	
	putChar('\n');

	IFS1bits.AD1IF = 0;	// Reset AD1IF
}
