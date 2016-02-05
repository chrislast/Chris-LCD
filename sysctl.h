#ifndef SYSCTL_H
#define SYSCTL_H

// p231
#define SYSCTL_BASE (0x400FE000)

#define SYSCTL_RIS      (*((volatile unsigned long *)(SYSCTL_BASE+0x050))) // Raw interrupt status p243
#define SYSCTL_RCC      (*((volatile unsigned long *)(SYSCTL_BASE+0x060))) // Run-Mode Clock Configuration p253
#define SYSCTL_RCC2     (*((volatile unsigned long *)(SYSCTL_BASE+0x070))) // Run-Mode Clock Configuration 2 p259
#define SYSCTL_GPIOHBCTL (*((volatile unsigned long *)(SYSCTL_BASE+0x06C))) // GPIO High-Performance Bus Control p257

#define SYSCTL_RCGCGPIO (*((volatile unsigned long *)(SYSCTL_BASE+0x608))) // GPIO Run Mode Clock Gating Control p339
#define SYSCTL_RCGCUART (*((volatile unsigned long *)(SYSCTL_BASE+0x618))) // UART Run Mode Clock Gating Control p343
#define SYSCTL_RCGCSSI  (*((volatile unsigned long *)(SYSCTL_BASE+0x61C))) // SSI Run Mode Clock Gating Control p345
#define SYSCTL_RCGCI2C  (*((volatile unsigned long *)(SYSCTL_BASE+0x620))) // I2C Run Mode Clock Gating Control p347
#define SYSCTL_RCGCUSB  (*((volatile unsigned long *)(SYSCTL_BASE+0x628))) // USB Run Mode Clock Gating Control p349
#define SYSCTL_RCGCCAN  (*((volatile unsigned long *)(SYSCTL_BASE+0x634))) // CAN Run Mode Clock Gating Control p350
#define SYSCTL_RCGCADC  (*((volatile unsigned long *)(SYSCTL_BASE+0x638))) // ADC Run Mode Clock Gating Control p351
#define SYSCTL_RCGCPWM  (*((volatile unsigned long *)(SYSCTL_BASE+0x640))) // PWM Run Mode Clock Gating Control p353

#define PERIPH_BASE (0xE000E000)

// SYSTICK timer
#define SYSTICK_RELOAD_VALUE 0x1fe
#define PERIPH_STCTRL    (*((volatile unsigned long *)(PERIPH_BASE+0x0010))) // SysTick Control and Status Register p136
#define PERIPH_STRELOAD  (*((volatile unsigned long *)(PERIPH_BASE+0x0014))) // SysTick Reload Value Register p138
#define PERIPH_STCURRENT (*((volatile unsigned long *)(PERIPH_BASE+0x0018))) // SysTick Current Value Register p139

void sysctl_init(void);
void Delay1ms(unsigned long msec);
#endif
