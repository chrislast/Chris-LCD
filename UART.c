#include "UART.h"
#include "sysctl.h"
#include "GPIO.h"

void UART_init(enum UART_e n)
{
	if (n==UART0)
	{
/* to be implemented
		unsigned long delay;
		// 1. Enable the SSI module using the RCGCSSI register (see page 345).
		SYSCTL_RCGCSSI |= 1;      // Enable SSI0
    // 2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 339).
		SYSCTL_RCGCGPIO |= 1;     // Enable GPIO PORT A
		delay = SYSCTL_RCGCGPIO;  // Wait for clock to start
		// 3. Set the GPIO AFSEL bits for the appropriate pins (see page 669).
		GPIO_PORTA_AFSEL_R |= 0x3C; // Enable SSI0 pins
		// 4. Configure the PMCn fields in the GPIOPCTL register to assign the SSI signals to the appropriate pins
		GPIO_PORTA_PCTL_R &= 0xFF0000FF;
		GPIO_PORTA_PCTL_R |= 0x00222200;
		// 5. Program the GPIODEN register to enable the pin's digital function
		GPIO_PORTA_DEN_R |= 0x3C;
*/		
	}
}
