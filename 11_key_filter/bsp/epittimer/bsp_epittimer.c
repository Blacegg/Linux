#include "bsp_epittimer.h"
#include "bsp_int.h"
#include "bsp_led.h"

void EPIT_Init(unsigned int frac, unsigned int value)
{
    if (frac > 0XFFF)
        frac = 0XFFF;
    EPIT1->CR = 0;
    EPIT1->CR = ((1 << 1) | (1 << 2) | (1 << 3) |
                 (frac << 4) | (1 << 24));
    EPIT1->LR = value;
    EPIT1->CMPR = 0;
    GIC_EnableIRQ(EPIT1_IRQn);
    system_register_irqhandler(EPIT1_IRQn,
                               (system_irq_handler_t)EPIT_IrqHandler,
                               NULL);
    EPIT1->CR |= (1 << 0);
}

void EPIT_IrqHandler(void)
{
    static unsigned char state = 0;
    state = !state;
    if ((EPIT1->SR) & (1 << 0))
    {
        led_switch(LED0, state);
    }
    EPIT1->SR |= (1 << 0);
}