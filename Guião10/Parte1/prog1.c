#include <detpic32.h>

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

return 0;
}
