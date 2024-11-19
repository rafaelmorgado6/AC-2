#include <detpic32.h>

void delay(int ms);

int main(void)
{
	// configuraçao ADC
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = 2-1; //2 conversoes
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1;
	
	TRISDbits.TRISD5 = 0;
	TRISB = TRISB & 0x80FF;
	
	int soma = 0;
	int media = 0;
	int aux;
	int i;
	
while(1)
{
	AD1CON1bits.ASAM = 1;		// Start conversion
	
	while( IFS1bits.AD1IF == 0 );	// Wait while conversion not done (AD1IF == 0)
	
	int *p = (int *)(&ADC1BUF0);
	for(i=0; i<16; i++)
	{
		aux = p[i*4];
		soma += aux;
	}
	media = soma/2;
	printInt(media, 16 | 3 << 16);
	putChar('\n');
	
	LATD = LATD & 0xFFDF ;		// reset display 1111 1111 1101 1111
	LATDbits.LATD5 = 1;		// ativar display menos significativo
	LATB = LATB & 0x80FF;		// reset segmentos 1000 0000 1111 1111
	
	if(media <= 102)
		LATB = LATB | 0x3F00;		// 0
	if((media > 102) && (media <= 204))
		LATB = LATB | 0x0600;		// 1
	if((media > 204) && (media <= 306))
		LATB = LATB | 0x5B00;		// 2
	if((media > 306) && (media <= 408))
		LATB = LATB | 0x4F00;		// 3
	if((media > 408) && (media <= 510))
		LATB = LATB | 0x6600;		// 4
	if((media > 510) && (media <= 612))
		LATB = LATB | 0x6D00;		// 5
	if((media > 612) && (media <= 714))
		LATB = LATB | 0x7D00;		// 6
	if((media > 714) && (media <= 816))
		LATB = LATB | 0x0700;		// 7
	if((media > 816) && (media <= 918))
		LATB = LATB | 0x7F00;		// 8	
	if(media > 918)
		LATB = LATB | 0x6F00;		// 9		
	
	
	media = 0;
	soma = 0;
	
	IFS1bits.AD1IF = 0;	//reset AD1IF
	
	delay(200);
}
	

return 0;
}

void delay(int ms)
{
	resetCoreTimer();
	while(readCoreTimer() < 20000*ms);
}