#ifndef NOKIA5110_LCD_H
#define NOKIA5110_LCD_H

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

#define LCD_SCLK (1L<<2) // PA2 - SSI0Clk
#define LCD_SCE  (1L<<3) // PA3 - SSI0Fss
#define LCD_DN   (1L<<5) // PA5 - SSI0Tx
#define LCD_DC   (1L<<6) // PA6 - D/C
#define LCD_RST  (1L<<7) // PA7 - RST
#define LCD_LED  (0) // NOT CONNECTED

#define LCD_BIAS_CONTROL (3)
#define LCD_TEMP_CONTROL (0)
#define LCD_CONTRAST     (0x3d)

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
