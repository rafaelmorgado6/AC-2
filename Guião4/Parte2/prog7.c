#include <detpic32.h>

int main(void)
{
	static const char disp7Scodes[] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

	TRISB = TRISB | 0x000F;		//configurar entradas 
	TRISB = TRISB & 0x80FF;		//configurar saidas (ter o cuidado de não alterar entradas)
	TRISD = TRISD & 0xFF9F;		//configurar saidas RD5 e RD6
	
	LATD = LATD & 0xFF9F;		//reset aos bits de saida display
	LATDbits.LATD6 = 1;		// só ativar o display mais significativo
	
	while(1)
	{
		int segments = PORTB & 0x000F;	//reset a tudo menos as entradas (read dip-switch)
					//vai ler o valor de entrada e guardar o valor escolhido
		
		int display= disp7Scodes[segments] << 8; // ir buscar o valor correspondente e
							// colocá -lo nos bits de saida
		
		
		LATB = LATB & 0x80FF;	//reset aos bits de saida
		LATB = LATB | display;	//enviar para o display 		
	}
	return 0;
}
