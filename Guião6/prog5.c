#include <detpic32.h>

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
	AD1CON2bits.SMPI = 4-1; 	// Interrupt is generated after N samples
					// (replace N by the desired number of
					// consecutive samples)

	AD1CHSbits.CH0SA = 4; 		// replace x by the desired input
					// analog channel (0 to 15)

	AD1CON1bits.ON = 1; 		// Enable A/D converter
					// This must the last command of the A/D
					// configuration sequence
					
	int i;
	int soma = 0;
	int VAL_AD = 0;
	int V = 0;
	int aux;
	
while(1)
{
	AD1CON1bits.ASAM = 1;		// Start conversion
	
	while( IFS1bits.AD1IF == 0 );	// Wait while conversion not done (AD1IF == 0)
	
	putChar('\r');
	
	//ACESSO AS 16 POSIÇOES DO BUFFER
	
	int *p = (int *)(&ADC1BUF0);
	for( i = 0; i < 16; i++ ) 
	{
		aux = p[i*4];			//colocar buffer numa posição de memória
		
		printInt(aux, 10 | 4 << 16);	//como N=4 irá aparecer 4 buffer com valor e o resto a 0 
		putChar(' ');
		
		soma += aux;			//calculo da soma de todos os buffers
	}
	
	VAL_AD = soma/4		// calculo da média
	
	V = (VAL_AD*33+511)/1023;	//calculo da amplitude max
	
	printStr("\nAmplitude da Tensão na entrada do conversor A/D: ");
	printInt(V, 10 | 4 << 16);	//só irá imprimir o número inteiro as casas decimais não serão impressas devido a truncatura

	putChar('\n');
	
	soma = 0;
	VAL_AD = 0;		//sem estas 2 linhas os calculos não dão os correspondidos
	
	IFS1bits.AD1IF = 0;	// Reset
}
return 0;
}
