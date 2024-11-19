#include <detpic32.h>

void delay(int ms);

void send2displays(unsigned char value);

unsigned char toBDC(unsigned char value);		// converte numeros para binario

int main(void){
	
	TRISB = TRISB | 0x0001;		//configuração RB0 como entrada

	TRISB = TRISB & 0x80FF;		// configuração RB8 - RB14 como saida
	TRISB = TRISB & 0xFF9F;		// configuraçao RD5 e RD5 como saida
	TRISE = TRISE & 0xFF00;		// configuraçao RE0 - RE7 como saida 
	
	int counter = 0;
	
	while(1)
	{
		int i = 0;
		do
		{
			int valor = toBCD(counter);	// converte counter para BCD
			send2displays(valor);		// envia valor em BDC para display
			delay(10);			
			
			LATE = LATE & 0xFF00;		// reset bits de saida
			LATE = LATE | valor		// colocar valor(BCD) nos bits de saida
	
		}while(++i < 50);		// 50 porque f counter tem de ser 2Hz = 500ms, ou seja 10*50 = 500
		
		int DS = PORTB & 0x0001;	// reset aos bits que não sao a entrada
		
		if(DS = 1)
		{
			counter++;	
		
			if(counter = 60)
				counter = 0;	//para nao ir para valores acima de 99 
		}
		if(DS = 0)
		{		
			if(counter = 0)
				counter = 60;	//para nao ir para valores abaixo de 0
				
			counter--;
		}
	}
	
return 0;
}

void delay(int ms)
{
	for(; ms>0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer()<2000;
	}
}

void send2displays(unsigned char value)
{
static const char display7Scodes[] = {0x3F, 0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6f,0x77,0x7C,0x39,0x5E,0x79,0x71};
static char displayFlag = 0;

	if(displayFlag = 0)
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

unsigned char toBDC(unsigned char value)
{
	return ((value / 10) << 4) + (value % 10);
}
