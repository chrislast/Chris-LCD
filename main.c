

// 1. Pre-processor Directives Section
#include "Nokia5110_LCD.h"
#include "GPIO.h"
#include "sysctl.h"
#include "SSI.h"

// Constant declarations to access port registers using 
// symbolic names instead of addresses

// 2. Declarations Section
//   Global Variables

//   Function Prototypes
void Delay1ms(unsigned long msec);

void SystemInit(void)
{
	sysctl_init();     // initialise system control registers
	SYSCTL_GPIOHBCTL |= 0x08;  // Enable AHB for GPIO port D
	LCD_init();        // Initialise the LCD  
  SSI_init(SSI0);    // Enable SSI0
	// Enable UART0
}

// 3. Subroutines Section
int main(void){
  SystemInit();
  while(1)
	{
  }
}

// Subroutine to delay in units of milliseconds
// Inputs:  Number of milliseconds to delay
// Outputs: None
// Notes:   assumes 80 MHz clock
void Delay1ms(unsigned long msec){
// write this function
	  unsigned long i,j;
	  while (msec-- > 0)
			for (i=14; i>0; i--)
				for (j=1000; j>0; j--);
}

