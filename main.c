
#define NOKIA5110 1
#define CF128X128 2
#define LCD CF128X128

#include <stdlib.h>

// 1. Pre-processor Directives Section
#include "..\\tm4c123gh6pm.h"
#if (LCD == NOKIA5110)
 #include "Nokia5110_LCD.h"
#elif (LCD == CF128X128)
 #include "crystalfontz128x128.h"
#endif

// Constant declarations to access port registers using 
// symbolic names instead of addresses

// 2. Declarations Section
//   Global Variables

//   Function Prototypes
void init(void);
void Delay1ms(unsigned long msec);

// 3. Subroutines Section
int main(void)
{
#if (LCD == NOKIA5110)

	init();
	LCD_init();        // Initialise the LCD
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
#elif (LCD == CF128X128)
	setup();
	Initialize_LCD();
	Fill_LCD(0x80,0x80,0x80);
	while (1)
	{
		/*
		LCD_Line(  0,  0, 60, 60,0xff,   0,   0);
		LCD_Line(  0, 60, 30, 60,0xff,0xff,   0);
		LCD_Line(  0,127, 60, 67,0   ,0xff,   0);
		LCD_Line( 60,127, 59, 97,0   ,0xff,0xff);
		LCD_Line(127,127, 67, 67,0   ,0   ,0xff);
		LCD_Line(127, 67, 97, 68,0xff,0   ,0xff);
		LCD_Line(127,  0, 67, 60,0xff,0xff,0xff);
		LCD_Line( 67,  0, 67, 30,0x00,0x00,0x00);
		*/
		LCD_Line( rand()&0x7f,rand()&0x7f,rand()&0x7f,rand()&0x7f,
							rand()&0xff,rand()&0xff,rand()&0xff);
	}
	loop();
#endif
}

#define SYSTICK_RELOAD_VALUE (0x01FE)
void init(void)
{
	/* // Leave 16MHz clock at 16 MHz not 80MHz
	SYSCTL_RCC2 |= 0x80000000; // RCC2 overrides RCC
	SYSCTL_RCC2 |= 0x00000800; // system clock is derived from OSC using divisor SYSDIV2
	SYSCTL_RCC = 0x00000540;
	SYSCTL_RCC2 |= 0x41000000; // Divide PLL using 400 MHz
	SYSCTL_RCC2 &= ~0x00000800; // Use Main oscillator */
  
	
	/* Setup SysTick clock */
	// Set RELOAD value
	NVIC_ST_RELOAD_R = SYSTICK_RELOAD_VALUE;
	// Zero CURRENT value
  NVIC_ST_CURRENT_R=0;
	// Stop counter
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
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
