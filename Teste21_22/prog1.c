#include <detpic32.h>

void delay(int ms);

int main(void)
{
	TRISE = TRISE & 0xFFC0;	// configurar saida  1111 1111 1100 0000
	TRISB = TRISB & 0x0004;	//configurar entrada 0000 0000 0000 0100
	// ou TRISBbits.TRISB2 = 1
	
	int counter = 1;
	
while(1)
{
	LATE = LATE & 0xFFC0;		// reset saida
	PORTB = PORTB & 0x0004;		// reset entrada
	
	LATE = LATE | counter;		// chuta counter para a saida
	counter = counter << 1;		// shifta os bits do counter
	
	if(PORTBbits.RB2 == 0)
	{
		
		delay(333);		// 1000/f	f = 3Hz
	}
	else
	{
		delay(143);		// 1000/f	f = 7Hz
	}
	
	if(counter == 0x0040)		// 0000 0000 0100 0000
		counter = 0x0001;
		
}	
return 0;
}

void delay(int ms)
{
	resetCoreTimer();
	while(readCoreTimer() < 20000*ms);
}
