#ifndef UART_H
#define UART_H

#define UART0_BASE_ADDRESS (0x4000C000)
#define UART1_BASE_ADDRESS (0x4000D000)
#define UART2_BASE_ADDRESS (0x4000E000)
#define UART3_BASE_ADDRESS (0x4000F000)
#define UART4_BASE_ADDRESS (0x40010000)
#define UART5_BASE_ADDRESS (0x40011000)
#define UART6_BASE_ADDRESS (0x40012000)
#define UART7_BASE_ADDRESS (0x40013000)


#define UART0_DATA_R (*((volatile unsigned long *)(UART0_BASE_ADDRESS + 0x0000))) // UARTDR p903
#define UART0_CTL_R  (*((volatile unsigned long *)(UART0_BASE_ADDRESS + 0x0030))) // UARTCTL p915
#define UART0_CLKC_R (*((volatile unsigned long *)(UART0_BASE_ADDRESS + 0x0FC8))) // UARTCC  p936


enum UART_e
{
	UART0,
	UART1,
	UART2,
	UART3,
	UART4,
	UART5,
	UART6,
	UART7
};

void UART_init(enum UART_e n);

#endif
