#ifndef SSI_H
#define SSI_H

#define SSI0_BASE_ADDRESS (0x40008000)
#define SSI1_BASE_ADDRESS (0x40009000)
#define SSI2_BASE_ADDRESS (0x4000A000)
#define SSI3_BASE_ADDRESS (0x4000B000)

#define SSI0_CTL0_R (*((volatile unsigned long *)(SSI0_BASE_ADDRESS + 0x0000))) // SSICR0 p964
#define SSI0_CTL1_R (*((volatile unsigned long *)(SSI0_BASE_ADDRESS + 0x0004))) // SSICR1 p966
#define SSI0_DATA_R (*((volatile unsigned long *)(SSI0_BASE_ADDRESS + 0x0008))) // SSIDR  p968
#define SSI0_STAT_R (*((volatile unsigned long *)(SSI0_BASE_ADDRESS + 0x000C))) // SSISR  p969
#define SSI0_CLKC_R (*((volatile unsigned long *)(SSI0_BASE_ADDRESS + 0x0FC8))) // SSICC  p981
#define SSI0_CPSR_R (*((volatile unsigned long *)(SSI0_BASE_ADDRESS + 0x0010))) // SSI Clock Prescale (SSICPSR) p971

#define SSI_FRAME_FORMAT_FREESCALE_SPI         (0L<<4)
#define SSI_FRAME_FORMAT_TI_SYNCHRONOUS_SERIAL (1L<<4)
#define SSI_FRAME_FORMAT_MICROWIRE             (2L<<4)

#define SSI_SR_BUSY              (1<<4)
#define SSI_SR_RX_FIFO_FULL      (1<<3)
#define SSI_SR_RX_FIFO_NOT_EMPTY (1<<2)
#define SSI_SR_TX_FIFO_NOT_FULL  (1<<1)
#define SSI_SR_TX_FIFO_EMPTY     (1<<0)

enum SSI_e
{
	SSI0,
	SSI1,
	SSI2,
	SSI3
};

void SSI_init(enum SSI_e n);

void SSI_write(unsigned char byte);

#endif
