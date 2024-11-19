#include <detpic32.h>

void putc(char byte);

void putstr(char *str);

void delay(unsigned int ms);

int main(void)
{
// Configure UART2:

	int baudrate = 1200;
	int N = 16;
	
// 1 - Configure BaudRate Generator
	U2BRG = ((20000000 + 8*baudrate)/(N*baudrate)) - 1;

// 2 – Configure number of data bits, parity and number of stop bits (see U2MODE register)
	U2MODEbits.STSEL = 1;	// 2 Stop Bit
	U2MODEbits.PDSEL = 0x10;// 8 data bits, sem paridade 

// 3 – Enable the trasmitter and receiver modules (see register U2STA)
	U2STAbits.UTXEN = 1;	// Transmitter enable
	U2STAbits.URXEN = 1;	// Receiver enable
	
// 4 – Enable UART2 (see register U2MODE)
	U2MODEbits.ON = 1;		// Enable UART2

while(1)
{
	putstr("String de teste\n");
	delay(1000);
}


return 0;
}

void putc(char byte)
{
	while(U2STAbits.UTXBF == 1);	// wait while UART2 UTXBF == 1
	U2TXREG = byte;			// Copy "byte" to the U2TXREG register
}

void putstr(char *str)
{
	for(;*str!='\0';*str++) // use putc() function to send each charater ('\0' should not be sent)
		putc(*str);
}

void delay(unsigned int ms)
{
	resetCoreTimer();
	while(readCoreTimer() < 20000*ms);
}
