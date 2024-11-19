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
