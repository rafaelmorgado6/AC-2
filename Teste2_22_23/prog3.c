#include <detpic32.h>

volatile unsigned counter=15;

void putc(char byte);

int main(void)
{
	//config UART
	U2BRG = (20000000+8*9600)/(16*9600)-1;
	U2MODEbits.PDSEL = 2;			// odd parity(10)
	U2MODEbits.STSEL = 1;			// 2 stop bits
	
	U2STAbits.UTXEN = 1;
	U2STAbits.URXEN = 1;
	
	U2MODEbits.ON = 1;
	
	//config LEDS
	TRISE = TRISE & 0xFFE1;		// 111 1111 1110 0001
	
	//congif interrupts
	U2STAbits.URXISEL=0;				//recetor ligado
	U2STAbits.UTXISEL=0;				//transmissor desligado
	
	IEC1bits.U2RXIE=1;				//enable do recetor
	IEC1bits.U2TXIE=0;				//disable do transmissor
	
	IPC8bits.U2IP=1;				//prioridade
	
	IFS1bits.U2RXIF=0;
	
	EnableInterrupts();
	
	while(1);
	
return 0;
}
void putc(char byte)
{
	while(U2STAbits.UTXBF == 1);
		U2TXREG = byte;
}

void _int_(32) isr_uart2(void)
{
	char *str = "Reset\n";
	char c;
	
	if(IFS1bits.U2RXIF == 1)
	{
		c = U2RXREG;
	
	if(c == 'U')
	{
		counter++;
		
		if(counter == 16)
			counter = 0;
			
	}
	if(c == 'R')
	{
		counter = 0; 
		
		for(; *str != '\0'; str++)
			putc(*str);
			
	}
	LATE = LATE & 0xFFE1;		//reset leds
	
	LATE = LATE | (counter<<1);
	
	IFS1bits.U2RXIF = 0;
	}
}

