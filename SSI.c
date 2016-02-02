#include "SSI.h"
#include "sysctl.h"
#include "GPIO.h"

/*
To enable and initialize the SSI, the following steps are necessary:
1. Enable the SSI module using the RCGCSSI register (see page 345).
2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 339).
To find out which GPIO port to enable, refer to Table 23-5 on page 1346.
3. Set the GPIO AFSEL bits for the appropriate pins (see page 669). To determine which GPIOs to
configure, see Table 23-4 on page 1339.
4. Configure the PMCn fields in the GPIOPCTL register to assign the SSI signals to the appropriate
pins. See page 686 and Table 23-5 on page 1346.
5. Program the GPIODEN register to enable the pin's digital function. In addition, the drive strength,
drain select and pull-up/pull-down functions must be configured. Refer to �General-Purpose
Input/Outputs (GPIOs)� on page 648 for more information.
Note: Pull-ups can be used to avoid unnecessary toggles on the SSI pins which can take the
slave to a wrong state. */

void SSI_init(enum SSI_e n)
{
	if (n==SSI0)
	{
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
	}
}