#include <detpic32.h>

void delay(int ms);

int main(void)
{
	TRISE = (TRISE & 0xFF87);	   	// 1111 1111 1000 0111 = 0xFF87
						// RE6 a RE3 como saida
while(1){

	int count;
	for(count=0;count<11;count++){
		delay(250);
		int print =count<<3;
		LATE = (LATE & 0xFF87) | print;		// 1111  1111  1000  0111									
	}						//	print = 000  1
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
