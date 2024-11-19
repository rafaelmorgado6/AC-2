#include <detpic32.h>

#pragma config FNOSC = PRIPLL
#pragma config POSCMOD = HS
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_1
#pragma config FPBDIV = DIV_2

#define ADC_CONFIG1 0x00E4
#define ADC_CONFIG2 0x0000
#define ADC_CONFIG3 0x0100

void delay(int ms);

int main() {
    TRISDbits.TRISD11 = 0;   // Configure RD11 as output
    LATDbits.LATD11 = 1;     // Set RD11 high

    // Configure ADC
    AD1PCFG = 0xFFFF;        // Disable analog inputs
    AD1CON1 = ADC_CONFIG1;
    AD1CON2 = ADC_CONFIG2;
    AD1CON3 = ADC_CONFIG3;

    // Start ADC
    AD1CHSbits.CH0SA = 0;    // Select AN0 as input channel
    AD1CON1bits.SAMP = 1;    // Start sampling
    while (!AD1CON1bits.DONE); // Wait for conversion to complete
    delay(1000);
    AD1CON1bits.DONE = 0;    // Clear conversion done flag

    LATDbits.LATD11 = 0;     // Set RD11 low

    // Measure conversion time
    // Use an oscilloscope to measure the time RD11 is high

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

