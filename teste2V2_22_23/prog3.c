#include <detpic32.h>

volatile unsigned int counter = 0;

void putc(char byte);

int main(void)
{
	//config UART
	U2BRG = (20000000+8*2400)/(16*2400)-1;
	U2MODEbits.PDSEL = 1;			// even parity(01)
	U2MODEbits.STSEL = 1;			// 2 stop bits
	
	U2STAbits.UTXEN = 1;
	U2STAbits.URXEN = 1;
	
	U2MODEbits.ON = 1;
	
	//congif interrupts
	U2STAbits.URXISEL=0;				//recetor ligado
	U2STAbits.UTXISEL=0;				//transmissor desligado
	
	IEC1bits.U2RXIE=1;				//enable do recetor
	IEC1bits.U2TXIE=0;				//disable do transmissor
	
	IPC8bits.U2IP=1;				//prioridade
	
	IFS1bits.U2RXIF=0;
	
	EnableInterrupts();
	
	// config dos leds
	TRISE = TRISE & 0xFFF0;	// 1111 1111 1111 0000
	
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
	char *str = "VALOR MINIMO\n";
	char c;
	
	if(IFS1bits.U2RXIF == 1)
	{
		c = U2RXREG;
	if(c == 'F')
	{
		counter++;
		
		if(counter == 11)
			counter = 0;
	}
	if(c == 'C')
	{
		counter = 0;
		
		for(; *str != '\0'; str++)
			putc(*str);
	}
	LATE = LATE & 0xFFF0;
	
	LATE = LATE | counter;


	}
	IFS1bits.U2RXIF = 0;
}
