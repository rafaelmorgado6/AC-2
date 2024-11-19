#include <detpic32.h>

int main(void){
	int i;
	
		// Configuração do porto
	TRISBbits.TRISB4 = 1;	// Porto RB4 como input
	AD1PCFGbits.PCFG4 = 0;	// RB4 como analog input
	AD1CON1bits.SSRC = 7;	
	
	AD1CON1bits.CLRASAM = 1;
	
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = 1 - 1;
	
	AD1CHSbits.CH0SA = 4;
	
	AD1CON1bits.ON = 1;
	
		// Programa
		
	while(1){
	AD1CON1bits.ASAM = 1;	// Começar conversão
	
	while(IFS1bits.AD1IF == 0);	// Esperar enquanto a conversão não está pronta
	
	int *p = (int *)(&ADC1BUF0);
	for(i = 0; i<26; i++){
		printInt(p[i*4], 10);
		putChar(' ');
	}
	
	IFS1bits.AD1IF = 0;	// Reset
	}	
		
	return 0;
}
