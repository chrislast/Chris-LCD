#include "..\\tm4c123gh6pm.h"
#include "TM4C123.h"

void init_16MHz(void)
{
	// Set clock to 16 MHz
	SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;   // RCC2 overrides RCC
	SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;   // system clock is derived from OSC using divisor SYSDIV2
	SYSCTL_RCC_R   = SYSCTL_RCC_XTAL_16MHZ;
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2; // Use Main oscillator */
}

#define SYSCTL_SYSDIV_2_5  (0x04 << 22)

void init_80MHz(void)
{
  // 80 MHz clock
  // bus frequency is 400MHz/(SYSDIV2+1) = 400MHz/(4+1) = 80 MHz
  // configure the system to get its clock from the PLL
  // 0) configure the system to use RCC2 for advanced features
  //    such as 400 MHz PLL and non-integer System Clock Divisor
  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
  // 1) bypass PLL while initializing
  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
  // 2) select the crystal value and oscillator source
  SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   // clear XTAL field
  SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;// configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;// clear oscillator source field
  SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;// configure for main oscillator source
  // 3) activate PLL by clearing PWRDN
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
  // 4) set the desired system divider and the system divider least significant bit
  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  // use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) // clear system clock divider field
                  + SYSCTL_SYSDIV_2_5;      // configure for 80 MHz clock
  // 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}

void init_systick (unsigned long reload_value)
{
  /* Setup SysTick clock */
	// Set RELOAD value
	NVIC_ST_RELOAD_R = reload_value;
	// Zero CURRENT value
  NVIC_ST_CURRENT_R=0;
	// Stop counter
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
}

/*
#define GPIO_PCTL_PB0_T2CCP0    0x00000007  // T2CCP0 on PB0
#define GPIO_PCTL_PB1_T2CCP1    0x00000070  // T2CCP1 on PB1
#define GPIO_PCTL_PB2_T3CCP0    0x00000700  // T3CCP0 on PB2
#define GPIO_PCTL_PB3_T3CCP1    0x00007000  // T3CCP1 on PB3
#define GPIO_PCTL_PB4_T1CCP0    0x00070000  // T1CCP0 on PB4
#define GPIO_PCTL_PB5_T1CCP1    0x00700000  // T1CCP1 on PB5
#define GPIO_PCTL_PB6_T0CCP0    0x07000000  // T0CCP0 on PB6
#define GPIO_PCTL_PB7_T0CCP1    0x70000000  // T0CCP1 on PB7
#define GPIO_PCTL_PC0_T4CCP0    0x00000007  // T4CCP0 on PC0
#define GPIO_PCTL_PC1_T4CCP1    0x00000070  // T4CCP1 on PC1
#define GPIO_PCTL_PC2_T5CCP0    0x00000700  // T5CCP0 on PC2
#define GPIO_PCTL_PC3_T5CCP1    0x00007000  // T5CCP1 on PC3
#define GPIO_PCTL_PC4_WT0CCP0   0x00070000  // WT0CCP0 on PC4
#define GPIO_PCTL_PC5_WT0CCP1   0x00700000  // WT0CCP1 on PC5
#define GPIO_PCTL_PC6_WT1CCP0   0x07000000  // WT1CCP0 on PC6
#define GPIO_PCTL_PC7_WT1CCP1   0x70000000  // WT1CCP1 on PC7
#define GPIO_PCTL_PD0_WT2CCP0   0x00000007  // WT2CCP0 on PD0
#define GPIO_PCTL_PD1_WT2CCP1   0x00000070  // WT2CCP1 on PD1
#define GPIO_PCTL_PD2_WT3CCP0   0x00000700  // WT3CCP0 on PD2
#define GPIO_PCTL_PD3_WT3CCP1   0x00007000  // WT3CCP1 on PD3
#define GPIO_PCTL_PD4_WT4CCP0   0x00070000  // WT4CCP0 on PD4
#define GPIO_PCTL_PD5_WT4CCP1   0x00700000  // WT4CCP1 on PD5
#define GPIO_PCTL_PD6_WT5CCP0   0x07000000  // WT5CCP0 on PD6
#define GPIO_PCTL_PD7_WT5CCP1   0x70000000  // WT5CCP1 on PD7
#define GPIO_PCTL_PF0_T0CCP0    0x00000007  // T0CCP0 on PF0
#define GPIO_PCTL_PF1_T0CCP1    0x00000070  // T0CCP1 on PF1
#define GPIO_PCTL_PF2_T1CCP0    0x00000700  // T1CCP0 on PF2
#define GPIO_PCTL_PF3_T1CCP1    0x00007000  // T1CCP1 on PF3
#define GPIO_PCTL_PF4_T2CCP0    0x00070000  // T2CCP0 on PF4
*/
void sleep(unsigned long delay)
{
// 1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making any changes.
	TIMER0_CTL_R &= ~TIMER_CTL_TAEN;
// 2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.
	TIMER0_CFG_R &= TIMER_CFG_32_BIT_TIMER;
// 3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
//    a. Write a value of 0x1 for One-Shot mode.
//    b. Write a value of 0x2 for Periodic mode.
	TIMER0_TAMR_R &= ~TIMER_TAMR_TAMR_M;
	TIMER0_TAMR_R |= TIMER_TAMR_TAMR_1_SHOT;
// 4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
//    to select whether to capture the value of the free-running timer at time-out, use an external
//    trigger to start counting, configure an additional trigger or interrupt, and count up or down.
	TIMER0_TAMR_R &= ~TIMER_TAMR_TACDIR; // count down
// 5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
	TIMER0_TAILR_R;
// 6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register (GPTMIMR).
	TIMER0_IMR_R;
// 7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
	TIMER0_CTL_R;
// 8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
//    the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
//    Register (GPTMICR).
	while (TIMER0_RIS_R);
// If the TnMIE bit in the GPTMTnMR register is set, the RTCRIS bit in the GPTMRIS register is set,
// and the timer continues counting. In One-Shot mode, the timer stops counting after the time-out
// event. To re-enable the timer, repeat the sequence. A timer configured in Periodic mode reloads
// the timer and continues counting after the time-out event.

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
