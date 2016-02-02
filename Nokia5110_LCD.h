#ifndef NOKIA5110_LCD_H
#define NOKIA5110_LCD_H

#include "GPIO.h"
#include "SSI.h"

/*
  Hardware:
    Graphic LCD Pin ---------- TM4C123GHXL
       1-VCC       ----------------  3.3V
       2-GND       ----------------  GND
       3-SCE       ----------------  GPIO PORT D PIN 0
       4-RST       ----------------  GPIO PORT D PIN 1
       5-D/C       ----------------  GPIO PORT D PIN 2
       6-DN(MOSI)  ----------------  SSI/SPI DATA
       7-SCLK      ----------------  SSI/SPI CLK
       8-LED       - 330 Ohm res --  GPIO PORT D PIN 3
*/

// Map LCD GPIO outputs to Port D
#define LCD_GPIO_DATA_R  (GPIO_PORTD_DATA_R)
#define LCD_GPIO_AMSEL_R (GPIO_PORTD_AMSEL_R)
#define LCD_GPIO_PCTL_R  (GPIO_PORTD_PCTL_R)
#define LCD_GPIO_DIR_R   (GPIO_PORTD_DIR_R)
#define LCD_GPIO_AFSEL_R (GPIO_PORTD_AFSEL_R)
#define LCD_GPIO_PUR_R   (GPIO_PORTD_PUR_R)    
#define LCD_GPIO_DEN_R   (GPIO_PORTD_DEN_R)

#define LCD_SCE  (1L<<0) // PIN0
#define LCD_RST  (1L<<1) // PIN1
#define LCD_DC   (1L<<2) // PIN2
#define LCD_LED  (1L<<3) // PIN3

// Use default SSI PORT A [5:2]
#define LCD_SSI_DATA_R (SSI0_DATA_R)

#define SYSCTL_RCGCGPIO_CLKD (0x00000008)
#define LCD_GPIO_CLOCK_ENABLE (SYSCTL_RCGCGPIO_CLKD)

enum LCD_DISPLAY_CONTROL
{
	LCD_DISPLAY_BLANK,
	LCD_DISPLAY_NORMAL_MODE,
	LCD_DISPLAY_ALL_ON,
	LCD_DISPLAY_INVERSE_VIDEO
};

struct LCD_bitmap {
	unsigned char pixel[48][84];
};

void LCD_display_char (char c);
void LCD_display_string (char *c);
void LCD_display_bitmap (struct LCD_bitmap *bitmap);
void LCD_set_cursor (int x, int y);
void LCD_display_control (enum LCD_DISPLAY_CONTROL command);
void LCD_init(void);
void LCD_clear_screen(void);
void LCD_test_pattern(int pattern);
#endif
