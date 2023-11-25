#include "bsp_gpio.h"

void GPIO_Init(GPIO_Type *base, int pin, GPIO_Pin_Config_t *config)
{
    base->IMR &= ~(1U << pin);

    if (config->Direction == kGPIO_DigitalInput)
    {
        base->GDIR &= ~(0X1 << pin);
    }
    else if (config->Direction == kGPIO_DigitalOutput)
    {
        base->GDIR |= (0x1 << pin);
        GPIO_PinWrite(base, pin, config->OutputLogic);
    }

    GPIO_IntConfig(base, pin, config->interruptMode);
}

int GPIO_PinRead(GPIO_Type *base, int pin)
{
    return ((base->DR) >> pin & 0x1);
}

void GPIO_PinWrite(GPIO_Type *base, int pin, int value)
{
    if (value == 0U)
    {
        base->DR &= ~(0X1 << pin);
    }
    else if (value == 1U)
    {
        base->DR |= (0x1 << pin);
    }
}

void GPIO_IntConfig(GPIO_Type *base, unsigned int pin,
                    GPIO_Interrupt_Mode_t pin_int_mode)
{
    volatile uint32_t *icr;
    uint32_t icrShift;

    icrShift = pin;

    base->EDGE_SEL &= ~(1U << pin);

    if (pin < 16)
    {
        icr = &(base->ICR1);
    }
    else
    {
        icr = &(base->ICR2);
        icrShift -= 16;
    }

    switch (pin_int_mode)
    {
    case (kGPIO_IntLowLevel):
        *icr &= ~(3U << (2 * icrShift));
        break;

    case (kGPIO_IntHighLevel):
        *icr = (((*icr) & (~(3U << (2 * icrShift)))) |
                (1U << (2 * icrShift)));
        break;

    case (kGPIO_IntRisingEdge):
        *icr = (((*icr) & (~(3U << (2 * icrShift)))) |
                (2U << (2 * icrShift)));
        break;

    case (kGPIO_IntFallingEdge):
        *icr |= (3U << (2 * icrShift));
        break;

    case (kGPIO_IntRisingOrFallingEdge):
        base->EDGE_SEL |= (1U << pin);
        break;

    default:
        break;
    }
}

void GPIO_EnableInt(GPIO_Type *base, unsigned int pin)
{
    base->IMR |= (1 << pin);
}

void GPIO_DisableInt(GPIO_Type *base, unsigned int pin)
{
    base->IMR &= ~(1 << pin);
}

void GPIO_ClearIntFlags(GPIO_Type *base, unsigned int pin)
{
    base->ISR |= (1 << pin);
}