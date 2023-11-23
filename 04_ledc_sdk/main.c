#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

void clk_enable()
{
    CCM->CCGR0 = 0xffffffff;
    CCM->CCGR1 = 0xffffffff;
    CCM->CCGR2 = 0xffffffff;
    CCM->CCGR3 = 0xffffffff;
    CCM->CCGR4 = 0xffffffff;
    CCM->CCGR5 = 0xffffffff;
    CCM->CCGR6 = 0xffffffff;
}

void led_init()
{
    /* 1����ʼ�� IO ����, ����Ϊ GPIO1_IO03 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);

    /* 2������ GPIO1_IO03 �� IO ����
     *bit 16:0 HYS �ر�
     *bit [15:14]: 00 Ĭ������
     *bit [13]: 0 kepper ����
     *bit [12]: 1 pull/keeper ʹ��
     *bit [11]: 0 �رտ�·���
     *bit [7:6]: 10 �ٶ� 100Mhz
     *bit [5:3]: 110 R0/6 ��������
     *bit [0]: 0 ��ת����
     */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0X10B0);

    /* 3����ʼ�� GPIO, GPIO1_IO03 ����Ϊ��� */
    GPIO1->GDIR |= (1 << 3);

    /* 4������ GPIO1_IO03 ����͵�ƽ���� LED0 */
    GPIO1->DR &= ~(1 << 3);
}

void led_on()
{
    GPIO1->DR &= ~(1 << 3);
}

void led_off()
{
    GPIO1->DR |= (1 << 3);
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

int main()
{
    clk_enable();
    led_init();

    while (1)
    {
        led_on();
        delay(500);

        led_off();
        delay(500);
    }

    return 0;
}