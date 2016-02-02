#include "sysctl.h"

void sysctl_init(void)
{
	SYSCTL_RCC2 |= 0x80000000; // RCC2 overrides RCC
	SYSCTL_RCC2 |= 0x00000800; // system clock is derived from OSC using divisor SYSDIV2
	SYSCTL_RCC = 0x00000540;
	SYSCTL_RCC2 |= 0x41000000; // Divide PLL using 400 MHz
	SYSCTL_RCC2 &= ~0x00000800; // Use Main oscillator
}

