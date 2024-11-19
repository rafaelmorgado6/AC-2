#include <detpic32.h>

void delay(int ms);

void send2displays(unsigned char value);

int main(void)
{
	TRISB = (TRISB & 0x80FF);	// configuração RD8 - RD14 como saida 1000 0000 1111 1111
	TRISD = (TRISD & 0xFF9F);	// configuraçao RD5 e RD6  como saida 1111 1111 1001 1111
	
	LATB = (LATB & 0x80FF);			// 1000 0000 1111 1111

	
while(1){	
	send2displays(0x69);	 // imprime 69 nos displays		
	delay(100);
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

void send2displays(unsigned char value)
{
	char dh;
	char dl;

	static const char disp7Scodes[] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
	
	LATD = LATD & 0xFF9F;	//reset aos bits de saida 1111 1111 1001 1111
	LATDbits.LATD6 = 1;	// ativa display mais significativo
	
	dh = value >> 4;	//enviar o digito mais significativo para o display
	int display= disp7Scodes[dh] << 8;
	LATB = LATB & 0x80FF;	//reset aos bits de saida
	LATB = LATB | display;	//enviar para o display 
	
	LATDbits.LATD6 = 0;	//desligar display high
	LATDbits.LATD5 = 1;	//display menos significativo
	
	dl = value & 0x0F;	//enviar o digito menos significativo para o display
	display= disp7Scodes[dl] << 8;
	LATB = LATB & 0x80FF;	//reset aos bits de saida 1000 0000 1111 1111
	LATB = LATB | display;	//enviar para o display 
}
