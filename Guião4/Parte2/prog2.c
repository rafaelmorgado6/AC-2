#include <detpic32.h>

void delay(int ms);

int main(void)
{
	unsigned char segment;
	
	LATD = LATD & 0xFF9F;	//reset aos bits de saida do display	1111 1111 1001 1111
	LATDbits.LATD5=1;	//ligar o display menos significativo
	
	TRISB = TRISB & 0x80FF;	//configuração da saida B	1000 0000 1111 1111
	TRISD = TRISD & 0xFF9F;	//configuração da saida D	1111 1111 1001 1111
	
	int i;	//dá erro se declarar dentro do loop wtf \o_o/
	
	while(1)
	{
		segment=1;
		
		for(i=0; i< 7 ; i++)
		{
			LATB = LATB & 0x80FF;	//reset aos bits de saida	1000 0000 1111 1111
			LATB = LATB | (segment<<8); //seg<<8 para colocar a partir do bit8 e 
						    //depois colocar o valor do mesmo no LATB
			
			delay(500);	//f=2Hz = 0.5s
			segment=segment << 1;	//para alterar o segmento do display
		}	
		
		LATD = LATD ^ 0x0060;	//toggle do display (não dá para fazer com negação
					//sem se utilizar uma tomada de decisão) 0000 0000 0110 0000			
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
