#include <detpic32.h>

void delay(int ms);

void send2displays(unsigned char value);


int main(void)
{
	TRISB = (TRISB & 0x80FF);		// 1000 0000 1111 1111
	TRISD = (TRISD & 0xFF9F);		// 1111 1111 1001 1111
	
	while(1){

			send2displays(0x21);
			delay(200);
	}	
	return 0;
}

void send2displays(unsigned char value)
{
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C,0x39, 0x5E, 0x79, 0x71};
	static char displayFlag = 0;	// Mudar entre o RD5 e RD6
	
	int digit_low = value & 0x0F;	
	int digit_high = value >> 4;
	
	if(displayFlag == 0)
	{
		LATD = (LATD & 0xFF9F) | 0x0020;
		LATB = (LATB & 0x00FF) | (display7Scodes[digit_low] << 8);
	}
	else
		{
			LATD = (LATD & 0xFF9F) | 0x0040;
			LATB = (LATB & 0x00FF) | (display7Scodes[digit_high] << 8);
		}
		displayFlag = !displayFlag; // Mudar entre o RD5 e RD6
	
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

