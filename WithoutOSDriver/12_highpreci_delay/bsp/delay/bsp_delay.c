#include "bsp_delay.h"

void Delay_Init(void)
{
    GPT1->CR = 0;
    GPT1->CR |= (1 << 15);
    while (((GPT1->CR) >> 15) & 0X01)
    {
    };

    GPT1->CR |= (1 << 6);
    GPT1->PR = 65;
    GPT1->OCR[0] = 0XFFFFFFFF;
    GPT1->CR |= (1 << 0);

#if 0

    GPT1->CR |= (1 << 6);
    GPT1->PR = 65;
    GPT1->OCR[0] = 0X500000;
    GPT1->IR |= (1 << 0);

    GIC_EnableIRQ(GPT1_IRQn);
    system_register_irqhandler(GPT1_IRQn,
                               (system_irq_handler_t)GPT1_IrqHandler,
                               NULL);

#endif
}

#if 0

void GPT1_IrqHandler(void)
{
    static unsigned char state = OFF;
    state = !state;
    if ((GPT1->SR) & (0X1 << 0))
    {
        led_switch(LED0, state);
    }
    GPT1->SR &= ~(1 << 0);
}

#endif

void Delay_us(unsigned int usdelay)
{
    unsigned long oldcnt, newcnt;
    unsigned long tcntvalue = 0;

    oldcnt = GPT1->CNT;
    while (1)
    {
        newcnt = GPT1->CNT;
        if (oldcnt != newcnt)
        {
            if (newcnt > oldcnt)
                tcntvalue += (newcnt - oldcnt);
            else
                tcntvalue += 0XFFFFFFFF - newcnt + oldcnt;
            oldcnt = newcnt;
            if (tcntvalue >= usdelay)
                break;
        }
    }
}

void Delay_ms(unsigned int msdelay)
{
    int i = 0;
    for (i = 0; i < msdelay; i++)
    {
        Delay_us(1000);
    }
}

void delay_short(volatile unsigned int n)
{
    while (n--)
    {
    }
}

void delay(volatile unsigned int n)
{
    while (n--)
    {
        delay_short(0x7ff);
    }
}
