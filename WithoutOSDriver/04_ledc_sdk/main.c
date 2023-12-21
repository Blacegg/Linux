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
    /* 1、初始化 IO 复用, 复用为 GPIO1_IO03 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);

    /* 2、配置 GPIO1_IO03 的 IO 属性
     *bit 16:0 HYS 关闭
     *bit [15:14]: 00 默认下拉
     *bit [13]: 0 kepper 功能
     *bit [12]: 1 pull/keeper 使能
     *bit [11]: 0 关闭开路输出
     *bit [7:6]: 10 速度 100Mhz
     *bit [5:3]: 110 R0/6 驱动能力
     *bit [0]: 0 低转换率
     */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0X10B0);

    /* 3、初始化 GPIO, GPIO1_IO03 设置为输出 */
    GPIO1->GDIR |= (1 << 3);

    /* 4、设置 GPIO1_IO03 输出低电平，打开 LED0 */
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