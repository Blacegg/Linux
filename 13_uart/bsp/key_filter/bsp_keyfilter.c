#include "bsp_keyfilter.h"

void FilterKey_Init(void)
{
    GPIO_Pin_Config_t key_config;

    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0XF080);

    key_config.Direction = kGPIO_DigitalInput;
    key_config.interruptMode = kGPIO_IntFallingEdge;
    key_config.OutputLogic = 1;
    GPIO_Init(GPIO1, 18, &key_config);

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn,
                               (system_irq_handler_t)GPIO1_16_31_IrqHandler,
                               NULL);

    GPIO_EnableInt(GPIO1, 18);
    FilterTimer_Init(66000000 / 100);
}

void FilterTimer_Init(unsigned int value)
{
    EPIT1->CR = 0;
    EPIT1->CR = ((1 << 1) | (1 << 2) | (1 << 3) | (1 << 24));
    EPIT1->LR = value;
    EPIT1->CMPR = 0;

    GIC_EnableIRQ(EPIT1_IRQn);
    system_register_irqhandler(EPIT1_IRQn,
                               (system_irq_handler_t)FilterTimer_IrqHandler,
                               NULL);
}

void FilterTimer_Stop(void)
{
    EPIT1->CR &= ~(1 << 0);
}

void FilterTimer_Restart(unsigned int value)
{
    EPIT1->CR &= ~(1 << 0);
    EPIT1->LR = value;
    EPIT1->CR |= (1 << 0);
}

void FilterTimer_IrqHandler(void)
{
    static unsigned char state = OFF;
    if ((EPIT1->SR) & (1 << 0))
    {
        FilterTimer_Stop();
        if (GPIO_PinRead(GPIO1, 18) == 0)
        {
            state = !state;
            beep_switch(state);
        }
    }
    EPIT1->SR &= ~(1 << 0);
}

void GPIO1_16_31_IrqHandler(void)
{
    FilterTimer_Restart(66000000 / 100);
    GPIO_ClearIntFlags(GPIO1, 18);
}
