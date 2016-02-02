#ifndef GPIO_H
#define GPIO_H

#define GPIO_PORTA_APB (0x40004000) // Legacy GPIO Port A base address
#define GPIO_PORTB_APB (0x40005000) // Legacy GPIO Port B base address
#define GPIO_PORTC_APB (0x40006000) // Legacy GPIO Port C base address
#define GPIO_PORTD_APB (0x40007000) // Legacy GPIO Port D base address
#define GPIO_PORTE_APB (0x40024000) // Legacy GPIO Port E base address
#define GPIO_PORTF_APB (0x40025000) // Legacy GPIO Port F base address

#define GPIO_PORTA_AHB (0x40058000) // High speed GPIO Port A base address
#define GPIO_PORTB_AHB (0x40059000) // High speed GPIO Port B base address
#define GPIO_PORTC_AHB (0x4005A000) // High speed GPIO Port C base address
#define GPIO_PORTD_AHB (0x4005B000) // High speed GPIO Port D base address
#define GPIO_PORTE_AHB (0x4005C000) // High speed GPIO Port E base address
#define GPIO_PORTF_AHB (0x4005D000) // High speed GPIO Port F base address

#define GPIO_PORTA_BASE (GPIO_PORTA_AHB) // use high-speed
#define GPIO_PORTB_BASE (GPIO_PORTB_AHB) // use high-speed
#define GPIO_PORTC_BASE (GPIO_PORTC_AHB) // use high-speed
#define GPIO_PORTD_BASE (GPIO_PORTD_AHB) // use high-speed
#define GPIO_PORTE_BASE (GPIO_PORTE_AHB) // use high-speed
#define GPIO_PORTF_BASE (GPIO_PORTF_AHB) // use high-speed

#define GPIO_DATA_OFFSET  (0x0)
#define GPIO_DIR_OFFSET   (0x400)
#define GPIO_AFSEL_OFFSET (0x420)
#define GPIO_PUR_OFFSET   (0x510)
#define GPIO_DEN_OFFSET   (0x51C)
#define GPIO_LOCK_OFFSET  (0x520)
#define GPIO_CR_OFFSET    (0x524)
#define GPIO_AMSEL_OFFSET (0x528)
#define GPIO_PCTL_OFFSET  (0x52C)

#define GPIO_PORTA_DATA_R     (*((volatile unsigned long *)(GPIO_PORTA_BASE + GPIO_DATA_OFFSET + 0x3FC)))
#define GPIO_PORTA_DIR_R      (*((volatile unsigned long *)(GPIO_PORTA_BASE + GPIO_DIR_OFFSET)))
#define GPIO_PORTA_AFSEL_R    (*((volatile unsigned long *)(GPIO_PORTA_BASE + GPIO_AFSEL_OFFSET)))
#define GPIO_PORTA_PUR_R      (*((volatile unsigned long *)(GPIO_PORTA_BASE + GPIO_PUR_OFFSET)))
#define GPIO_PORTA_DEN_R      (*((volatile unsigned long *)(GPIO_PORTA_BASE + GPIO_DEN_OFFSET)))
#define GPIO_PORTA_LOCK_R     (*((volatile unsigned long *)(GPIO_PORTA_BASE + GPIO_LOCK_OFFSET)))
#define GPIO_PORTA_CR_R       (*((volatile unsigned long *)(GPIO_PORTA_BASE + GPIO_CR_OFFSET)))
#define GPIO_PORTA_AMSEL_R    (*((volatile unsigned long *)(GPIO_PORTA_BASE + GPIO_AMSEL_OFFSET)))
#define GPIO_PORTA_PCTL_R     (*((volatile unsigned long *)(GPIO_PORTA_BASE + GPIO_PCTL_OFFSET)))
	
#define GPIO_PORTD_DATA_R     (*((volatile unsigned long *)(GPIO_PORTD_BASE + GPIO_DATA_OFFSET + 0x3FC)))
#define GPIO_PORTD_DIR_R      (*((volatile unsigned long *)(GPIO_PORTD_BASE + GPIO_DIR_OFFSET)))
#define GPIO_PORTD_AFSEL_R    (*((volatile unsigned long *)(GPIO_PORTD_BASE + GPIO_AFSEL_OFFSET)))
#define GPIO_PORTD_PUR_R      (*((volatile unsigned long *)(GPIO_PORTD_BASE + GPIO_PUR_OFFSET)))
#define GPIO_PORTD_DEN_R      (*((volatile unsigned long *)(GPIO_PORTD_BASE + GPIO_DEN_OFFSET)))
#define GPIO_PORTD_LOCK_R     (*((volatile unsigned long *)(GPIO_PORTD_BASE + GPIO_LOCK_OFFSET)))
#define GPIO_PORTD_CR_R       (*((volatile unsigned long *)(GPIO_PORTD_BASE + GPIO_CR_OFFSET)))
#define GPIO_PORTD_AMSEL_R    (*((volatile unsigned long *)(GPIO_PORTD_BASE + GPIO_AMSEL_OFFSET)))
#define GPIO_PORTD_PCTL_R     (*((volatile unsigned long *)(GPIO_PORTD_BASE + GPIO_PCTL_OFFSET)))
	
#define GPIO_PORTF_DATA_R     (*((volatile unsigned long *)(GPIO_PORTF_BASE + GPIO_DATA_OFFSET + 0x3FC)))
#define GPIO_PORTF_DIR_R      (*((volatile unsigned long *)(GPIO_PORTF_BASE + GPIO_DIR_OFFSET)))
#define GPIO_PORTF_AFSEL_R    (*((volatile unsigned long *)(GPIO_PORTF_BASE + GPIO_AFSEL_OFFSET)))
#define GPIO_PORTF_PUR_R      (*((volatile unsigned long *)(GPIO_PORTF_BASE + GPIO_PUR_OFFSET)))
#define GPIO_PORTF_DEN_R      (*((volatile unsigned long *)(GPIO_PORTF_BASE + GPIO_DEN_OFFSET)))
#define GPIO_PORTF_LOCK_R     (*((volatile unsigned long *)(GPIO_PORTF_BASE + GPIO_LOCK_OFFSET)))
#define GPIO_PORTF_CR_R       (*((volatile unsigned long *)(GPIO_PORTF_BASE + GPIO_CR_OFFSET)))
#define GPIO_PORTF_AMSEL_R    (*((volatile unsigned long *)(GPIO_PORTF_BASE + GPIO_AMSEL_OFFSET)))
#define GPIO_PORTF_PCTL_R     (*((volatile unsigned long *)(GPIO_PORTF_BASE + GPIO_PCTL_OFFSET)))

enum GPIO_PORT
{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F
};

#endif
