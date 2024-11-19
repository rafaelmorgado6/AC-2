#include <detpic32.h>

void delay(int ms);

void send2displays(unsigned char value);

int main(void)
{
	TRISB = (TRISB & 0x80FF);		// 1000 0000 1111 1111
	TRISD = (TRISD & 0xFF9F);		// 1111 1111 1001 1111
	
	LATB = (LATB & 0x80FF);

	
while(1){	
	send2displays(0x15);		// imprime 15 nos displays		
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
static const char display7Scodes[] = {0x3F, 0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6f};
static char displayFlag = 0;

	char digit_low = value & 0x0F;
	char digit_high = value >> 4;

	if(displayFlag == 0){
	LATDbits.LATD5 = 0;			// RD5 = 0, não ativa disply 
	LATDbits.LATD6 = 1;			// RD6 = 1, ativa display
						// select display high	
						// send digit_high (dh) to display
	LATB = (LATB & 0x80FF) | display7Scodes[digit_high] << 8;	// int display= disp7Scodes[dh] << 8;
	}								// LATB = LATB & 0x80FF;
									// LATB = LATB | display;
	else
	{
	LATDbits.LATD6 = 0;			// RD6 = 0, não ativa display
	LATDbits.LATD5 = 1;			// RD5 = 1, ativa disply 
						// select display low				
						// send digit_low (dl) to display 0x0F
	
	LATB = (LATB & 0x80FF) | display7Scodes[digit_low] << 8;
	}
	displayFlag = !displayFlag;
	
	return 0;
}
