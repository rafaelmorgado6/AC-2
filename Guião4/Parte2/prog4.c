#include <detpic32.h>

void delay(int ms);

int main(void)
{
	unsigned char segment;
	
	LATD = LATD & 0xFF9F;	//reset aos bits de saida do display
	LATD = LATD | 0x0020;	//RD5=1 e RD6=0 mesma coisa que ter:
				//LATD = (LATD & 0xFF9F) | 0X0020
	
	TRISB = TRISB & 0x80FF;	//configuração da saida B
	TRISD = TRISD & 0xFF9F;	//configuração da saida D
	
	int i;	//dá erro se declarar dentro do loop wtf \o_o/
	
	while(1)
	{
		segment=1;
		
		for(i=0; i< 7 ; i++)
		{
			LATB = LATB & 0x80FF;	//reset aos bits de saida
			LATB = LATB | (segment<<8); //seg<<8 para colocar a partir do bit8 e 
						    //depois colocar o valor do mesmo no LATB
			
			delay(100);	//f=10Hz ALTERAR AQUI OS VALORES EM MS: 100/20/10
			
			segment=segment << 1;	//para alterar o segmento do display
		}	
		
		LATD = LATD ^ 0x0060;	//toggle do display (não dá para fazer com negação
					//sem se utilizar uma tomada de decisão)			
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
