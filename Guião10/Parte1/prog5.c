#include <detpic32.h>

void putc(char byte);

char getc(void);

void delay(unsigned int ms);

int main(void)
{
// Configure UART2:

	int baudrate = 115200;
	int N = 16;
	
// 1 - Configure BaudRate Generator
	U2BRG = ((20000000 + 8*baudrate)/(N*baudrate)) - 1;

// 2 – Configure number of data bits, parity and number of stop bits (see U2MODE register)
	U2MODEbits.STSEL = 0;	// 1 Stop Bit
	U2MODEbits.PDSEL = 0x00;// 8 data bits, sem paridade 

// 3 – Enable the trasmitter and receiver modules (see register U2STA)
	U2STAbits.UTXEN = 1;	// Transmitter enable
	U2STAbits.URXEN = 1;	// Receiver enable
	
// 4 – Enable UART2 (see register U2MODE)
	U2MODEbits.ON = 1;		// Enable UART2

	char C;
while(1)
{
	
	C = getc();// Read character using getc()
	putc(C);// Send character using putc()
}


return 0;
}

char getc(void)
{	
	char C;
	while(U2STAbits.URXDA == 0);	// wait while UART2 UTXBF == 0
	C = U2RXREG;
	return C;			
}
void putc(char byte)
{
	while(U2STAbits.UTXBF == 1);	// wait while UART2 UTXBF == 1
	U2TXREG = byte;			// Copy "byte" to the U2TXREG register
}

void delay(unsigned int ms)
{
	resetCoreTimer();
	while(readCoreTimer() < 20000*ms);
}
