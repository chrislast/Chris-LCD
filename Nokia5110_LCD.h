#ifndef NOKIA5110_LCD_H
#define NOKIA5110_LCD_H

#include "GPIO.h"
#include "SSI.h"

// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected, consists of 4 white LEDs which draw ~80mA total

// Map LCD GPIO outputs to Port D
#define LCD_GPIO_DATA_R  (GPIO_PORTA_DATA_R)
#define LCD_GPIO_AMSEL_R (GPIO_PORTA_AMSEL_R)
#define LCD_GPIO_PCTL_R  (GPIO_PORTA_PCTL_R)
#define LCD_GPIO_DIR_R   (GPIO_PORTA_DIR_R)
#define LCD_GPIO_AFSEL_R (GPIO_PORTA_AFSEL_R)
#define LCD_GPIO_PUR_R   (GPIO_PORTA_PUR_R)    
#define LCD_GPIO_DEN_R   (GPIO_PORTA_DEN_R)

#define LCD_SCLK (1L<<2) // PA2 - SSI0Clk
#define LCD_SCE  (1L<<3) // PA3 - SSI0Fss
#define LCD_DN   (1L<<5) // PA5 - SSI0Tx
#define LCD_DC   (1L<<6) // PA6 - D/C
#define LCD_RST  (1L<<7) // PA7 - RST
#define LCD_LED  (0) // NOT CONNECTED

// Use default SSI0 on PORT A [5:2]
#define LCD_SSI_DATA_R (SSI0_DATA_R) // SSIDR p968
#define LCD_SSI_STAT_R (SSI0_STAT_R) // SSISR p969
#define LCD_SSI_CTL0_R (SSI0_CTL0_R) // SSICR0 p964
#define LCD_SSI_CTL1_R (SSI0_CTL1_R) // SSICR1 p966

#define LCD_SSI_FRAME_FORMAT (SSI_FRAME_FORMAT_FREESCALE_SPI)


#define SYSCTL_RCGCGPIO_CLKD (1L<<3)
#define SYSCTL_RCGCGPIO_CLKA (1L<<0)
#define LCD_GPIO_CLOCK_ENABLE (SYSCTL_RCGCGPIO_CLKA)

enum LCD_DISPLAY_CONTROL
{
	LCD_DISPLAY_BLANK,
	LCD_DISPLAY_NORMAL_MODE,
	LCD_DISPLAY_ALL_ON,
	LCD_DISPLAY_INVERSE_VIDEO
};

struct LCD_bitmap {
	unsigned char pixel[6][84];
};

void LCD_display_char (char c);
void LCD_display_string (char *c);
void LCD_display_bitmap (struct LCD_bitmap *bitmap);
void LCD_set_cursor (unsigned int x, unsigned int y);
void LCD_display_control (enum LCD_DISPLAY_CONTROL command);
void LCD_init(void);
void LCD_clear_screen(void);
void LCD_test_pattern(int pattern);
void LCD_power_on(void);
void LCD_power_off (void);
#endif
