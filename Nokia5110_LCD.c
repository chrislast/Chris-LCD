#include "..\\tm4c123gh6pm.h"
#include "Nokia5110_LCD.h"

void SSI_init(void);

/* PCD8544-specific defines: */
enum LCD_CD
{
	LCD_COMMAND,
	LCD_DATA
};

enum LCD_INSTRUCTION_SET
{
	LCD_BASIC_INSTRUCTION_SET=0x00,
	LCD_EXTENDED_INSTRUCTION_SET=0x01
};

enum LCD_ADDRESS_MODE
{
	LCD_HORIZONTAL_ADDRESSING=0x00,
	LCD_VERTICAL_ADDRESSING=0x02
};

enum LCD_POWER_STATUS
{
	LCD_POWER_ON=0x00,
	LCD_POWER_OFF=0x04
};

static enum LCD_ADDRESS_MODE address_mode;
static enum LCD_POWER_STATUS power_status;

/* 84x48 LCD Defines: */
#define LCD_WIDTH   84 // Note: x-coordinates go wide
#define LCD_WIDTH_CHARS (LCD_WIDTH/6)   // 14 chars wide
#define LCD_HEIGHT  48 // Note: y-coordinates go high
#define LCD_HEIGHT_CHARS (LCD_HEIGHT/8) // 6 chars high
#define WHITE       0  // For drawing pixels. A 0 draws white.
#define BLACK       1  // A 1 draws black.

#define LCD_COMMAND_FUNCTION_SET    0x20
#define LCD_COMMAND_DISPLAY_CONTROL 0x08
#define LCD_COMMAND_SET_X_ADDRESS   0x80
#define LCD_COMMAND_SET_Y_ADDRESS   0x40
#define LCD_COMMAND_TEMP_CONTROL    0x04
#define LCD_COMMAND_BIAS_SYSTEM     0x10
#define LCD_COMMAND_SET_CONTRAST    0x80

static const unsigned char ASCII[][5] = {
  // First 32 characters (0x00-0x19) are ignored. These are
  // non-displayable, control characters.
   {0x00, 0x00, 0x00, 0x00, 0x00} // 0x20  
  ,{0x00, 0x00, 0x5f, 0x00, 0x00} // 0x21 !
  ,{0x00, 0x07, 0x00, 0x07, 0x00} // 0x22 "
  ,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 0x23 #
  ,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 0x24 $
  ,{0x23, 0x13, 0x08, 0x64, 0x62} // 0x25 %
  ,{0x36, 0x49, 0x55, 0x22, 0x50} // 0x26 &
  ,{0x00, 0x05, 0x03, 0x00, 0x00} // 0x27 '
  ,{0x00, 0x1c, 0x22, 0x41, 0x00} // 0x28 (
  ,{0x00, 0x41, 0x22, 0x1c, 0x00} // 0x29 )
  ,{0x14, 0x08, 0x3e, 0x08, 0x14} // 0x2a *
  ,{0x08, 0x08, 0x3e, 0x08, 0x08} // 0x2b +
  ,{0x00, 0x50, 0x30, 0x00, 0x00} // 0x2c ,
  ,{0x08, 0x08, 0x08, 0x08, 0x08} // 0x2d -
  ,{0x00, 0x60, 0x60, 0x00, 0x00} // 0x2e .
  ,{0x20, 0x10, 0x08, 0x04, 0x02} // 0x2f /
  ,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 0x30 0
  ,{0x00, 0x42, 0x7f, 0x40, 0x00} // 0x31 1
  ,{0x42, 0x61, 0x51, 0x49, 0x46} // 0x32 2
  ,{0x21, 0x41, 0x45, 0x4b, 0x31} // 0x33 3
  ,{0x18, 0x14, 0x12, 0x7f, 0x10} // 0x34 4
  ,{0x27, 0x45, 0x45, 0x45, 0x39} // 0x35 5
  ,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 0x36 6
  ,{0x01, 0x71, 0x09, 0x05, 0x03} // 0x37 7
  ,{0x36, 0x49, 0x49, 0x49, 0x36} // 0x38 8
  ,{0x06, 0x49, 0x49, 0x29, 0x1e} // 0x39 9
  ,{0x00, 0x36, 0x36, 0x00, 0x00} // 0x3a :
  ,{0x00, 0x56, 0x36, 0x00, 0x00} // 0x3b ;
  ,{0x08, 0x14, 0x22, 0x41, 0x00} // 0x3c <
  ,{0x14, 0x14, 0x14, 0x14, 0x14} // 0x3d =
  ,{0x00, 0x41, 0x22, 0x14, 0x08} // 0x3e >
  ,{0x02, 0x01, 0x51, 0x09, 0x06} // 0x3f ?
  ,{0x32, 0x49, 0x79, 0x41, 0x3e} // 0x40 @
  ,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 0x41 A
  ,{0x7f, 0x49, 0x49, 0x49, 0x36} // 0x42 B
  ,{0x3e, 0x41, 0x41, 0x41, 0x22} // 0x43 C
  ,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 0x44 D
  ,{0x7f, 0x49, 0x49, 0x49, 0x41} // 0x45 E
  ,{0x7f, 0x09, 0x09, 0x09, 0x01} // 0x46 F
  ,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 0x47 G
  ,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 0x48 H
  ,{0x00, 0x41, 0x7f, 0x41, 0x00} // 0x49 I
  ,{0x20, 0x40, 0x41, 0x3f, 0x01} // 0x4a J
  ,{0x7f, 0x08, 0x14, 0x22, 0x41} // 0x4b K
  ,{0x7f, 0x40, 0x40, 0x40, 0x40} // 0x4c L
  ,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 0x4d M
  ,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 0x4e N
  ,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 0x4f O
  ,{0x7f, 0x09, 0x09, 0x09, 0x06} // 0x50 P
  ,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 0x51 Q
  ,{0x7f, 0x09, 0x19, 0x29, 0x46} // 0x52 R
  ,{0x46, 0x49, 0x49, 0x49, 0x31} // 0x53 S
  ,{0x01, 0x01, 0x7f, 0x01, 0x01} // 0x54 T
  ,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 0x55 U
  ,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 0x56 V
  ,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 0x57 W
  ,{0x63, 0x14, 0x08, 0x14, 0x63} // 0x58 X
  ,{0x07, 0x08, 0x70, 0x08, 0x07} // 0x59 Y
  ,{0x61, 0x51, 0x49, 0x45, 0x43} // 0x5a Z
  ,{0x00, 0x7f, 0x41, 0x41, 0x00} // 0x5b [
  ,{0x02, 0x04, 0x08, 0x10, 0x20} // 0x5c backslash
  ,{0x00, 0x41, 0x41, 0x7f, 0x00} // 0x5d ]
  ,{0x04, 0x02, 0x01, 0x02, 0x04} // 0x5e ^
  ,{0x40, 0x40, 0x40, 0x40, 0x40} // 0x5f _
  ,{0x00, 0x01, 0x02, 0x04, 0x00} // 0x60 `
  ,{0x20, 0x54, 0x54, 0x54, 0x78} // 0x61 a
  ,{0x7f, 0x48, 0x44, 0x44, 0x38} // 0x62 b
  ,{0x38, 0x44, 0x44, 0x44, 0x20} // 0x63 c
  ,{0x38, 0x44, 0x44, 0x48, 0x7f} // 0x64 d
  ,{0x38, 0x54, 0x54, 0x54, 0x18} // 0x65 e
  ,{0x08, 0x7e, 0x09, 0x01, 0x02} // 0x66 f
  ,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 0x67 g
  ,{0x7f, 0x08, 0x04, 0x04, 0x78} // 0x68 h
  ,{0x00, 0x44, 0x7d, 0x40, 0x00} // 0x69 i
  ,{0x20, 0x40, 0x44, 0x3d, 0x00} // 0x6a j 
  ,{0x7f, 0x10, 0x28, 0x44, 0x00} // 0x6b k
  ,{0x00, 0x41, 0x7f, 0x40, 0x00} // 0x6c l
  ,{0x7c, 0x04, 0x18, 0x04, 0x78} // 0x6d m
  ,{0x7c, 0x08, 0x04, 0x04, 0x78} // 0x6e n
  ,{0x38, 0x44, 0x44, 0x44, 0x38} // 0x6f o
  ,{0x7c, 0x14, 0x14, 0x14, 0x08} // 0x70 p
  ,{0x08, 0x14, 0x14, 0x18, 0x7c} // 0x71 q
  ,{0x7c, 0x08, 0x04, 0x04, 0x08} // 0x72 r
  ,{0x48, 0x54, 0x54, 0x54, 0x20} // 0x73 s
  ,{0x04, 0x3f, 0x44, 0x40, 0x20} // 0x74 t
  ,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 0x75 u
  ,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 0x76 v
  ,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 0x77 w
  ,{0x44, 0x28, 0x10, 0x28, 0x44} // 0x78 x
  ,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 0x79 y
  ,{0x44, 0x64, 0x54, 0x4c, 0x44} // 0x7a z
  ,{0x00, 0x08, 0x36, 0x41, 0x00} // 0x7b {
  ,{0x00, 0x00, 0x7f, 0x00, 0x00} // 0x7c |
  ,{0x00, 0x41, 0x36, 0x08, 0x00} // 0x7d }
  ,{0x10, 0x08, 0x08, 0x10, 0x08} // 0x7e ~
  ,{0x78, 0x46, 0x41, 0x46, 0x78} // 0x7f DEL
};


// LCD_SSI_DATA_R = SSIDR  p968
// LCD_SSI_STAT_R = SSISR  p969

static void LCD_write (enum LCD_CD cd, unsigned char byte)
{
	if (cd == LCD_COMMAND)
	{
		// Wait until SSI is idle
		while(SSI0_SR_R & SSI_SR_BSY);
	  GPIO_PORTA_DATA_R &= ~LCD_DC;  // clear DC bit for command
		
		// write command byte to serial port
		SSI0_DR_R = byte;
		
    // Wait for command to complete
		while(SSI0_SR_R & SSI_SR_BSY);
	  GPIO_PORTA_DATA_R |= LCD_DC;  // Set DC bit for data
	}
	else
	{
		// Wait until Tx FIFO is not full
		while (!(SSI0_SR_R & SSI_SR_TNF));
		// write data byte to serial port
		SSI0_DR_R = byte;
	}
}

void LCD_display_char (char c)
{
	if (c>=0x20 && c<=0x7f)
	{
		int i;
		for (i=0;i<5;i++)
		{
			LCD_write(LCD_DATA, ASCII[(c-0x20)][i]);
		}
	  LCD_write(LCD_DATA, 0x0); // Add a blank column
	}
}

void LCD_display_string (char *c)
{
  while (*c)
  	LCD_display_char(*c++);
}

void LCD_display_bitmap2 (struct LCD_bitmap *bitmap)
{
	unsigned char output;
	int i,j,k;
	LCD_set_cursor(0,0);
	for (i=0; i<(LCD_HEIGHT_CHARS); i++)
	{
		output = 0;
		for (j=0;j<(LCD_WIDTH);j++)
		{
			for (k=7;k>=0;k--)
			{
				output=output<<1;
				output+=((bitmap->pixel[j][k])&0x1);
				// write data word to LCD
				LCD_write(LCD_DATA,output);
			}
		}
	}
	LCD_set_cursor(0,0);
}

void LCD_display_bitmap (struct LCD_bitmap *bitmap)
{
	int i,j;
	LCD_set_cursor(0,0);
	for (i=0; i<(LCD_HEIGHT_CHARS); i++)
		for (j=0;j<(LCD_WIDTH);j++)
			LCD_write(LCD_DATA,bitmap->pixel[i][j]);
	LCD_set_cursor(0,0);
}

void LCD_display_random(void)
{
	int i;
	LCD_set_cursor(0,0);
	for (i=0; i<(LCD_HEIGHT_CHARS*LCD_WIDTH);i++)
	{
		LCD_write(LCD_DATA,(unsigned char)(NVIC_ST_CURRENT_R&0xFFL));
	}
	LCD_set_cursor(0,0);
}

void LCD_display_pixel(void)
{
	static unsigned int i=8*84*3+60;
	int x,y,shift;
	x=i%LCD_WIDTH;
	y=i/LCD_WIDTH/8;
	LCD_set_cursor(x,y);
	shift = (i/LCD_WIDTH)%8;
  LCD_write(LCD_DATA,(unsigned char)(WHITE));
  LCD_write(LCD_DATA,(unsigned char)(BLACK<<shift));
	if (++i >= LCD_HEIGHT*LCD_WIDTH-1)
		i=0;	LCD_set_cursor(0,0);
	LCD_display_string("###(");
	LCD_display_char((unsigned char)((x/10)+0x30));
	LCD_display_char((unsigned char)((x%10)+0x30));
	LCD_display_char(',');
	LCD_display_char((unsigned char)(y+0x30));	
	LCD_display_char(':');
	LCD_display_char((unsigned char)(shift+0x30));	
	LCD_display_string(")###");
}

static void LCD_instruction_set(enum LCD_INSTRUCTION_SET instruction_set)
{
	LCD_write(LCD_COMMAND,LCD_COMMAND_FUNCTION_SET|power_status|address_mode|instruction_set);
}

void LCD_set_cursor (unsigned int x, unsigned int y)
{
	LCD_instruction_set(LCD_BASIC_INSTRUCTION_SET);
	LCD_write(LCD_COMMAND,LCD_COMMAND_SET_X_ADDRESS|((unsigned char)(x&0x7F))); // set x address
	LCD_write(LCD_COMMAND,LCD_COMMAND_SET_Y_ADDRESS|((unsigned char)(y&0x7)));  // set y address
}

void LCD_display_control (enum LCD_DISPLAY_CONTROL command)
{
	enum display_control_bits {D=(1<<2),E=(1<<0)};
	switch(command)
	{
		case LCD_DISPLAY_BLANK:
			LCD_write(LCD_COMMAND,LCD_COMMAND_DISPLAY_CONTROL|0); break;
		case LCD_DISPLAY_NORMAL_MODE:
			LCD_write(LCD_COMMAND,LCD_COMMAND_DISPLAY_CONTROL|D); break;
		case LCD_DISPLAY_ALL_ON:
			LCD_write(LCD_COMMAND,LCD_COMMAND_DISPLAY_CONTROL|E); break;
		case LCD_DISPLAY_INVERSE_VIDEO:
			LCD_write(LCD_COMMAND,LCD_COMMAND_DISPLAY_CONTROL|D|E); break;
	}
	return;
}

void LCD_bias_control(unsigned long int n)
{
	LCD_instruction_set(LCD_EXTENDED_INSTRUCTION_SET);
	LCD_write(LCD_COMMAND,LCD_COMMAND_BIAS_SYSTEM|(n&0x07));
	LCD_instruction_set(LCD_BASIC_INSTRUCTION_SET);
}

void LCD_temp_control(unsigned long int n)
{
	LCD_instruction_set(LCD_EXTENDED_INSTRUCTION_SET);
	LCD_write(LCD_COMMAND,LCD_COMMAND_TEMP_CONTROL|(n&0x03));
	LCD_instruction_set(LCD_BASIC_INSTRUCTION_SET);
}

void LCD_contrast(unsigned long int n)
{
	LCD_instruction_set(LCD_EXTENDED_INSTRUCTION_SET);
	LCD_write(LCD_COMMAND,LCD_COMMAND_SET_CONTRAST|(n&0x7F));
	LCD_instruction_set(LCD_BASIC_INSTRUCTION_SET);
}

void LCD_init(void)
{
	volatile unsigned long temp;
	// use port defined in header file for LCD control lines
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;           // 1) Enable Port A clock
  temp = SYSCTL_RCGCGPIO_R;                          // delay to allow clock to stabilize     
  GPIO_PORTA_AMSEL_R= 0x00;                          // 2) disable analog function
  GPIO_PORTA_PCTL_R= 0x00000000;                     // 3) GPIO clear bit PCTL  
  GPIO_PORTA_DIR_R &= ~0x00;                         // 4.1) define inputs
  GPIO_PORTA_DIR_R |= (LCD_DC|LCD_RST);              // 4.2) define outputs  
  GPIO_PORTA_AFSEL_R= 0x00;                          // 5) no alternate function
  GPIO_PORTA_PUR_R= LCD_RST;                         // 6) enable pullup resistor for LCD reset
  GPIO_PORTA_DEN_R=(LCD_DC|LCD_RST);                 // 7) enable digital pins

	GPIO_PORTA_DATA_R &= ~LCD_RST; // Pulse !RST to reset LCD
	temp = GPIO_PORTA_DATA_R;      // delay
	GPIO_PORTA_DATA_R |= LCD_RST;  //
	
	SSI_init();    // Enable SSI0
	SSI0_CR1_R &= ~(SSI_CR1_SSE);    // Disable SSI Synchronous Serial Port
	SSI0_CR0_R = (SSI_CR0_DSS_8|SSI_CR0_FRF_MOTO);   // 8-bit data, Freescale SPI Frame Format
	SSI0_CR1_R |= (SSI_CR1_SSE);     // Enable SSI Synchronous Serial Port
	
	address_mode = LCD_HORIZONTAL_ADDRESSING;
	LCD_display_control(LCD_DISPLAY_NORMAL_MODE);
	LCD_bias_control(LCD_BIAS_CONTROL);
	LCD_temp_control(LCD_TEMP_CONTROL);
	LCD_contrast(LCD_CONTRAST);
	LCD_power_on();
	LCD_clear_screen();
}

void LCD_power_on(void)
{
	power_status = LCD_POWER_ON;
	LCD_write(LCD_COMMAND,LCD_COMMAND_FUNCTION_SET|power_status|address_mode);
}

void LCD_power_off(void)
{
	power_status = LCD_POWER_OFF;
	LCD_write(LCD_COMMAND,LCD_COMMAND_FUNCTION_SET|power_status|address_mode);
}

void LCD_clear_screen(void)
{
	int i;
	LCD_set_cursor(0,0);
	for (i=0; i<(LCD_HEIGHT*LCD_WIDTH/8); i++)
		LCD_write(LCD_DATA,WHITE);
	LCD_set_cursor(0,0);
}

void LCD_test_pattern(int pattern)
{
  struct LCD_bitmap test;
	switch(pattern)
	{
		case 1:
			LCD_display_char('x');
		  break;
		case 2:
			LCD_display_string("Hello World");
		  break;
		case 3:
			LCD_display_bitmap(&test);
		  break;
		case 4:
			LCD_display_random();
		  break;
		case 5:
			LCD_display_pixel();
		  break;
		default:
			LCD_display_string("Not implemented");
	}
}

void SSI_init(void)
{
		volatile unsigned long temp;
		// 1. Enable the SSI module using the RCGCSSI register (see page 345).
		SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R0;      // Enable SSI0
		temp = SYSCTL_RCGCSSI_R;
    // 2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 339).
		SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;     // Enable GPIO PORT A
		temp = SYSCTL_RCGCGPIO_R;
		// 3. Set the GPIO AFSEL bits for the appropriate pins (see page 669).
		GPIO_PORTA_AFSEL_R |= 0x2C; // Enable SSI0 pins
		// 4. Configure the PMCn fields in the GPIOPCTL register to assign the SSI signals to the appropriate pins
		GPIO_PORTA_PCTL_R &= 0xFF0F0000;
		GPIO_PORTA_PCTL_R |= 0x00202211; // Enable SSI0 and UART0
		// 5. Program the GPIODEN register to enable the pin's digital function
		GPIO_PORTA_DEN_R |= 0x2F;
		SSI0_CPSR_R = 0x18; // clock prescale copied from edX
}
