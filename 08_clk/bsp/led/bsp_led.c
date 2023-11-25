#include "bsp_led.h"

void led_init(void)
{
    /* 1、初始化 IO 复用 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);

    /* 2、、配置 GPIO1_IO03 的 IO 属性 */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0X10B0);

    //     /* 3、初始化 GPIO,GPIO1_IO03 设置为输出*/
    //     GPIO1->GDIR |= (1 << 3);

    //     /* 4、设置 GPIO1_IO03 输出低电平，打开 LED0*/
    //     GPIO1->DR &= ~(1 << 3);
    GPIO_Pin_Config_t led_config;
    led_config.Direction = kGPIO_DigitalOutput;
    led_config.OutputLogic = 0;
    GPIO_Init(GPIO1, 3, &led_config);
}

void led_switch(int led, int status)
{
    switch (led)
    {
    case LED0:
        GPIO_PinWrite(GPIO1, 3, status);
        // if (status == ON)
        //     GPIO1->DR &= ~(1 << 3); /* 打开 LED0 */
        // else if (status == OFF)
        //     GPIO1->DR |= (1 << 3); /* 关闭 LED0 */
        break;
    }
}
