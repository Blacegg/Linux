#include "bsp_clk.h"

/*
 * @description : ʹ�� I.MX6U ��������ʱ��
 * @param : ��
 * @return : ��
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

    /* �����ں�ʱ�ӣ���ARM_PLL1 */
    if ((((CCM->CCSR) >> 2) & 0X1) == 0)
    {
        /* ѡ��step_clk��ʱ��Դ */
        CCM->CCSR &= ~(1 << 8);
        /* �ı�ARM_PLL1��ʱ����Դ����ѡ��step_clk */
        CCM->CCSR |= (1 << 2);
    }
    /* �޸�PLL1��ʱ��Ϊ1056MHZ */
    CCM_ANALOG->PLL_ARM |= (1 << 13);
    CCM_ANALOG->PLL_ARM |= (88 << 0);
    /* ����ARM_PLL1����Ƶ */
    CCM->CACRR |= (1 << 0);
    /* �л�ʱ��Դ */
    CCM->CCSR &= ~(1 << 2);

    /* ����PLL2��4·PFD */
    reg = CCM_ANALOG->PFD_528;
    reg &= ~(0X3f3f3f3f);
    reg |= (32 << 24);
    reg |= (24 << 16);
    reg |= (16 << 8);
    reg |= (27 << 0);
    CCM_ANALOG->PFD_528 = reg;

    /* ����PLL3��4·PFD */
    reg = 0;
    reg = CCM_ANALOG->PFD_480;
    reg &= ~(0X3f3f3f3f);
    reg |= (19 << 24);
    reg |= (17 << 16);
    reg |= (16 << 8);
    reg |= (12 << 0);
    CCM_ANALOG->PFD_480 = reg;

    /* ����AHBʱ�� */
    CCM->CBCMR &= ~(3 << 18);
    CCM->CBCMR |= (1 << 18); // ����pre_periph_clk_sel
    CCM->CBCDR &= ~(1 << 25);
    while (((CCM->CDHIPR) >> 5) & 1)
    {
    };

#if 0
    CCM->CBCDR &= ~(7 << 10);
    CCM->CBCDR |= (2 << 10);
    while (((CCM->CDHIPR) >> 1) & 1)
    {
    };
#endif
    /* ����IPGʱ�� */
    CCM->CBCDR &= ~(3 << 8);
    CCM->CBCDR |= (1 << 8);

    /* ����PERCLKʱ�� */
    CCM->CSCMR1 &= ~(1 << 6);
    CCM->CSCMR1 &= ~(0X3F << 0);
}