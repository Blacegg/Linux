#include "bsp_gpio.h"

void GPIO_Init(GPIO_Type *base, int pin, GPIO_Pin_Config_t *config)
{
    if (config->Direction == kGPIO_DigitalInput)
    {
        base->GDIR &= ~(0X1 << pin);
    }
    else if (config->Direction == kGPIO_DigitalOutput)
    {
        base->GDIR |= (0x1 << pin);
        GPIO_PinWrite(base, pin, config->OutputLogic);
    }
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