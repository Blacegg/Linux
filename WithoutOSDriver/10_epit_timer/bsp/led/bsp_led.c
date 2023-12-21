#include "bsp_led.h"

void led_init(void)
{
    /* 1����ʼ�� IO ���� */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);

    /* 2�������� GPIO1_IO03 �� IO ���� */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0X10B0);

    //     /* 3����ʼ�� GPIO,GPIO1_IO03 ����Ϊ���*/
    //     GPIO1->GDIR |= (1 << 3);

    //     /* 4������ GPIO1_IO03 ����͵�ƽ���� LED0*/
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
        //  if (status == ON)
        //      GPIO1->DR &= ~(1 << 3); /* �� LED0 */
        //  else if (status == OFF)
        //      GPIO1->DR |= (1 << 3); /* �ر� LED0 */
        break;
    }
}
