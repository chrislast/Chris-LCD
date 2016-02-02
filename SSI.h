#ifndef SSI_H
#define SSI_H

#define SSI0_BASE_ADDRESS (0x40008000)
#define SSI1_BASE_ADDRESS (0x40009000)
#define SSI2_BASE_ADDRESS (0x4000A000)
#define SSI3_BASE_ADDRESS (0x4000B000)

#define SSI0_CTL0_R (*((volatile unsigned long *)(SSI0_BASE_ADDRESS + 0x0000))) // SSICR0 p966
#define SSI0_CTL1_R (*((volatile unsigned long *)(SSI0_BASE_ADDRESS + 0x0004))) // SSICR1 p968
#define SSI0_DATA_R (*((volatile unsigned long *)(SSI0_BASE_ADDRESS + 0x0008))) // SSIDR  p970
#define SSI0_STAT_R (*((volatile unsigned long *)(SSI0_BASE_ADDRESS + 0x000C))) // SSISR  p971
#define SSI0_CLKC_R (*((volatile unsigned long *)(SSI0_BASE_ADDRESS + 0x0FC8))) // SSICC  p981

enum SSI_e
{
	SSI0,
	SSI1,
	SSI2,
	SSI3
};

void SSI_init(enum SSI_e n);

#endif
