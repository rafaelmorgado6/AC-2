#include <detpic32.h>

void delay(unsigned int);
unsigned char toBcd(unsigned char);
void send2displays(unsigned char);

int main(void)
{
	TRISB = (TRISB & 0x80FF); //1000 0000 1111 1111 -> bits RB14-8 definidos como saida
	TRISD = (TRISD & 0xFF9F); //1111 1111 1001 1111 bits RD5-6 output
	
	
	TRISBbits.TRISB4 = 1; // RBx digital output disconnected
	AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
	AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
	// mode an internal counter ends sampling and starts conversion
	AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
	// interrupt is generated. At the same time,hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = 4-1; //N-1 Interrupt is generated after N samples
	// (replace N by the desired number of consecutive samples)
	AD1CHSbits.CH0SA = 4; // replace x by the desired input
	// analog channel (0 to 15)
	AD1CON1bits.ON = 1; // Enable A/D converter
	// This must the last command of the A/D
	// configuration sequence
	
	int i, soma, aux, media, V;
	unsigned char bcd;
while(1)
{
	if(i == 0) // 0, 200ms, 400ms, 600ms, ...
{
// Start conversion
	AD1CON1bits.ASAM = 1;
// Wait while conversion not done (AD1IF == 0)
	while( IFS1bits.AD1IF == 0 );
// Read conversion result (ADC1BUF0 value) and print it
	putChar('\r');
	int *p = (int *)(&ADC1BUF0);
	soma = 0;
// Convert analog input (4 samples)
	for( i = 0; i < 16; i++ ) {
	
		aux = p[i*4];
		//printInt(aux,10 | 4 << 16);
		//putChar(' ');
		
		soma += aux;
	}
// Read samples and calculate the average
	media = soma/4;
// Calculate voltage amplitude
	V = (media*33+511)/1023;
// Convert voltage amplitude to decimal
	bcd = toBcd(V); 
	
	soma = 0;
	media = 0;
	IFS1bits.AD1IF = 0;
}
// Send voltage value to displays
	send2displays(bcd);
// Wait 10 ms (using the core timer)
	delay(10);
	i = (i + 1) % 20 ;
	
	
	
	printInt10(V);
	putChar('\n');
// Reset AD1IF

}
		
return 0;
}

unsigned char toBcd(unsigned char value)
{
return ((value / 10) << 4) + (value % 10);
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

void delay(unsigned int t)
{
	resetCoreTimer();
	while(readCoreTimer() < 20000*t);
}
