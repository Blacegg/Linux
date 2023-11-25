#include "bsp_clk.h"

/*
 * @description : 使能 I.MX6U 所有外设时钟
 * @param : 无
 * @return : 无
 */

void clk_enable(void)
{
    CCM->CCGR0 = 0XFFFFFFFF;
    CCM->CCGR1 = 0XFFFFFFFF;
    CCM->CCGR2 = 0XFFFFFFFF;
    CCM->CCGR3 = 0XFFFFFFFF;
    CCM->CCGR4 = 0XFFFFFFFF;
    CCM->CCGR5 = 0XFFFFFFFF;
    CCM->CCGR6 = 0XFFFFFFFF;
}

void clk_init(void)
{
    int reg = 0;

    /* 设置内核时钟，即ARM_PLL1 */
    if ((((CCM->CCSR) >> 2) & 0X1) == 0)
    {
        /* 选择step_clk的时钟源 */
        CCM->CCSR &= ~(1 << 8);
        /* 改变ARM_PLL1的时钟来源，即选择step_clk */
        CCM->CCSR |= (1 << 2);
    }
    /* 修改PLL1的时钟为1056MHZ */
    CCM_ANALOG->PLL_ARM |= (1 << 13);
    CCM_ANALOG->PLL_ARM |= (88 << 0);
    /* 设置ARM_PLL1二分频 */
    CCM->CACRR |= (1 << 0);
    /* 切换时钟源 */
    CCM->CCSR &= ~(1 << 2);

    /* 设置PLL2的4路PFD */
    reg = CCM_ANALOG->PFD_528;
    reg &= ~(0X3f3f3f3f);
    reg |= (32 << 24);
    reg |= (24 << 16);
    reg |= (16 << 8);
    reg |= (27 << 0);
    CCM_ANALOG->PFD_528 = reg;

    /* 设置PLL3的4路PFD */
    reg = 0;
    reg = CCM_ANALOG->PFD_480;
    reg &= ~(0X3f3f3f3f);
    reg |= (19 << 24);
    reg |= (17 << 16);
    reg |= (16 << 8);
    reg |= (12 << 0);
    CCM_ANALOG->PFD_480 = reg;

    /* 设置AHB时钟 */
    CCM->CBCMR &= ~(3 << 18);
    CCM->CBCMR |= (1 << 18); // 设置pre_periph_clk_sel
    CCM->CBCDR &= ~(1 << 25);
    while (((CCM->CDHIPR) >> 5) & 1)
    {
    };
    CCM->CBCDR &= ~(7 << 10);
    CCM->CBCDR |= (2 << 10);
    while (((CCM->CDHIPR) >> 1) & 1)
    {
    };

    /* 设置IPG时钟 */
    CCM->CBCDR &= ~(3 << 8);
    CCM->CBCDR |= (1 << 8);

    /* 设置PERCLK时钟 */
    CCM->CSCMR1 &= ~(1 << 6);
    CCM->CSCMR1 &= ~(0X3F << 0);
}