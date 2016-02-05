

// 1. Pre-processor Directives Section
#include "Nokia5110_LCD.h"
#include "GPIO.h"
#include "sysctl.h"
#include "SSI.h"
#include "UART.h"

// Constant declarations to access port registers using 
// symbolic names instead of addresses

// 2. Declarations Section
//   Global Variables

//   Function Prototypes

void SystemInit(void)
{
	sysctl_init();     // initialise system control registers
	LCD_init();        // Initialise the LCD  
	// Enable UART0
	// UART_init(UART0);  // Enable UART0
}

// 3. Subroutines Section
int main(void)
{
  SystemInit();
  while(1)
	{
		int i;
		for (i=5;i<6;i++)
		{
			LCD_display_control(LCD_DISPLAY_NORMAL_MODE);
			LCD_test_pattern(i);
			Delay1ms(100);
		}
  }
}

