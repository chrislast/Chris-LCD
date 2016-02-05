#include "sysctl.h"

void sysctl_init(void)
{
	/* // Leave 16MHz clock at 16 MHz not 80MHz
	SYSCTL_RCC2 |= 0x80000000; // RCC2 overrides RCC
	SYSCTL_RCC2 |= 0x00000800; // system clock is derived from OSC using divisor SYSDIV2
	SYSCTL_RCC = 0x00000540;
	SYSCTL_RCC2 |= 0x41000000; // Divide PLL using 400 MHz
	SYSCTL_RCC2 &= ~0x00000800; // Use Main oscillator */
  
	
	/* Setup SysTick clock */
	// Set RELOAD value
	PERIPH_STRELOAD = SYSTICK_RELOAD_VALUE;
	// Zero CURRENT value
  PERIPH_STCURRENT=0;
	// Stop counter
	PERIPH_STCTRL = 0x05;
}

// Subroutine to delay in units of milliseconds
// Inputs:  Number of milliseconds to delay
// Outputs: None
// Notes:   assumes 16 MHz clock
void Delay1ms(unsigned long msec)
{
	  unsigned long j;
	  while (msec-- > 0)
				for (j=8000; j>0; j--);
}
