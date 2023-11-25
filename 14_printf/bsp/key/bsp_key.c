#include "bsp_key.h"

void Key_Init(void)
{
    GPIO_Pin_Config_t key_congig;

    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0XF080);

    key_congig.Direction = kGPIO_DigitalInput;
    GPIO_Init(GPIO1, 18, &key_congig);
}

int Key_GetValue(void)
{
    int ret = 0;
    static unsigned char release = 1;
    if ((release == 1) && (GPIO_PinRead(GPIO1, 18) == 0))
    {
        delay(10);
        release = 0;
        if (GPIO_PinRead(GPIO1, 18) == 0)
        {
            ret = KEY0_VALUE;
        }
    }
    else if (GPIO_PinRead(GPIO1, 18) == 1)
    {
        ret = 0;
        release = 1;
    }
    return ret;
}
