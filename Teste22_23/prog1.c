#include <detpic32.h>

void delay(int ms);

int main(void)
{

	TRISE = TRISE & 0xFFC3;	// config saidas 1111 1111 1100 0011
	TRISBbits.TRISB2 = 1;	// config entrada RB2 = 1

	int c = 0;
	int DS3;
	//double f=435;
	
while(1)
{
	LATE = LATE & 0xFFC3;	// reset saida
	DS3 = PORTBbits.RB2;
	LATE = LATE | (c<< 2);
	
	if(DS3 == 0)
		delay(435);		// 1000/2.3
		
	if(DS3 == 1)
		delay(193);
	
	c++;
	
	if(c == 10){
		c = 0;
		
		}
		
}	
return 0;
}

void delay(int ms)
{
	resetCoreTimer();
	while(readCoreTimer() < 20000*ms);
}
