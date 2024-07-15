#include <stdint.h>
#include <stdbool.h>

#define GPIO_PORTM ((volatile uint32_t *)0x40063000)
#define SYSCTL ((volatile uint32_t *)0x400FE000)
#define TIMER3 ((volatile uint32_t *)0x40033000)

#define GPIO_PIN_3  (1 << 3)

#define SYSCTL_RCGCGPIO_PORTM (1 << 11)
#define SYSCTL_RCGCTIMER3 (1 << 3)

#define TBEN (1 << 8)

enum {
  SYSCTL_RCGCGPIO = (0x608 >> 2),
  GPIO_DEN  =   (0x51c >> 2),
  SYSCTL_RCGCTIMER = (0x604 >> 2),
  GPIO_PCTL = (0x52C >> 2),
  GPTM_CTL = (0x00C >> 2),
  GPTM_CFG = (0x000 << 2),
  GPTM_TBMR = (0x008 >> 2),
  GPTM_BILR = (0x02C >> 2),
  GPTM_MATCH = (0x034 >> 2),
  GPIO_FSEL = (0x420 >> 2)
};

void main(void)
{
    SYSCTL[SYSCTL_RCGCTIMER] |= SYSCTL_RCGCTIMER3;
    SYSCTL[SYSCTL_RCGCGPIO] |= SYSCTL_RCGCGPIO_PORTM;
    SYSCTL[SYSCTL_RCGCGPIO] |= SYSCTL_RCGCGPIO_PORTM;

    GPIO_PORTM[GPIO_PCTL] |= 0x3000;
    GPIO_PORTM[GPIO_FSEL] |= 0x8;
    GPIO_PORTM[GPIO_DEN] |= GPIO_PIN_3;

    TIMER3[GPTM_CTL] &= ~TBEN;
    TIMER3[GPTM_CFG] |= 0x4;
    TIMER3[GPTM_TBMR] |= (0x8 | 0x2);
    TIMER3[GPTM_TBMR] &= ~(1 << 2);
    TIMER3[GPTM_CTL] &= ~(1 << 14);
    TIMER3[GPTM_BILR] = 0xA2C2;
    TIMER3[GPTM_MATCH] = 0x1046;
    TIMER3[GPTM_CTL] |= TBEN;

    while(true){
    }
}
