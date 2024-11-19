#include <detpic32.h>

void delay(int ms);

int main(void)
{
	TRISCbits.TRISC14 = 0;		// Configure port RC14 as output	
	while(1)
	{
	delay(500);
	LATCbits.LATC14 = !LATCbits.LATC14;		// Toggle RC14 port value
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
