#include "bsp_exit.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_delay.h"
#include "bsp_beep.h"

void EXIT_Init(void)
{
    GPIO_Pin_Config_t key_config;

    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    key_config.Direction = kGPIO_DigitalInput;
    key_config.interruptMode = kGPIO_IntFallingEdge;
    key_config.OutputLogic = 1;
    GPIO_Init(GPIO1, 18, &key_config);

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn,
                               (system_irq_handler_t)GPIO1_IO18_IrqHandler, NULL);
    GPIO_EnableInt(GPIO1, 18);
}

void GPIO1_IO18_IrqHandler(void)
{
    static unsigned char state = 0;
    delay(10);
    if (GPIO_PinRead(GPIO1, 18) == 0) /* 按键按下了 */
    {
        state = !state;
        beep_switch(state);
    }

    GPIO_ClearIntFlags(GPIO1, 18); /* 清除中断标志位 */
}