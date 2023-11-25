#include "bsp_lcd.h"

struct tftlcd_typedef tftlcd_dev;

void LCD_Init(void)
{
    LCDGPIO_Init();
    LCDCLK_Init(32, 3, 5);
}

void LCDGPIO_Init(void)
{
    GPIO_Pin_Config_t gpio_config;

    IOMUXC_SetPinMux(IOMUXC_LCD_DATA00_LCDIF_DATA00, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA01_LCDIF_DATA01, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA02_LCDIF_DATA02, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA03_LCDIF_DATA03, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA04_LCDIF_DATA04, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA05_LCDIF_DATA05, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA06_LCDIF_DATA06, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA07_LCDIF_DATA07, 0);

    IOMUXC_SetPinMux(IOMUXC_LCD_DATA08_LCDIF_DATA08, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA09_LCDIF_DATA09, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA10_LCDIF_DATA10, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA11_LCDIF_DATA11, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA12_LCDIF_DATA12, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA13_LCDIF_DATA13, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA14_LCDIF_DATA14, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA15_LCDIF_DATA15, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA16_LCDIF_DATA16, 0);

    IOMUXC_SetPinMux(IOMUXC_LCD_DATA17_LCDIF_DATA17, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA18_LCDIF_DATA18, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA19_LCDIF_DATA19, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA20_LCDIF_DATA20, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA21_LCDIF_DATA21, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA22_LCDIF_DATA22, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA23_LCDIF_DATA23, 0);

    IOMUXC_SetPinMux(IOMUXC_LCD_CLK_LCDIF_CLK, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_ENABLE_LCDIF_ENABLE, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_VSYNC_LCDIF_VSYNC, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_HSYNC_LCDIF_HSYNC, 0);
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_GPIO1_IO08, 0);

    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA00_LCDIF_DATA00, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA01_LCDIF_DATA01, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA02_LCDIF_DATA02, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA03_LCDIF_DATA03, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA04_LCDIF_DATA04, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA05_LCDIF_DATA05, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA06_LCDIF_DATA06, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA07_LCDIF_DATA07, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA08_LCDIF_DATA08, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA09_LCDIF_DATA09, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA10_LCDIF_DATA10, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA11_LCDIF_DATA11, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA12_LCDIF_DATA12, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA13_LCDIF_DATA13, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA14_LCDIF_DATA14, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA15_LCDIF_DATA15, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA16_LCDIF_DATA16, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA17_LCDIF_DATA17, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA18_LCDIF_DATA18, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA19_LCDIF_DATA19, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA20_LCDIF_DATA20, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA21_LCDIF_DATA21, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA22_LCDIF_DATA22, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA23_LCDIF_DATA23, 0xB9);

    IOMUXC_SetPinConfig(IOMUXC_LCD_CLK_LCDIF_CLK, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_ENABLE_LCDIF_ENABLE, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_HSYNC_LCDIF_HSYNC, 0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_VSYNC_LCDIF_VSYNC, 0xB9);

    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_GPIO1_IO08, 0xB9); /* 背光BL引脚 		*/

    /* GPIO初始化 */
    gpio_config.Direction = kGPIO_DigitalOutput; /* 输出 			*/
    gpio_config.OutputLogic = 1;                 /* 默认关闭背光 */
    gpio_init(GPIO1, 8, &gpio_config);           /* 背光默认打开 */
    gpio_pinwrite(GPIO1, 8, 1);                  /* 打开背光     */
}

void LCDCLK_Init(unsigned char loopDiv, unsigned char prediv, unsigned char div)
{
    /* 先初始化video pll
     * VIDEO PLL = OSC24M * (loopDivider + (denominator / numerator)) / postDivider
     *不使用小数分频器，因此denominator和numerator设置为0
     */
    CCM_ANALOG->PLL_VIDEO_NUM = 0; /* 不使用小数分频器 */
    CCM_ANALOG->PLL_VIDEO_DENOM = 0;

    /*
     * PLL_VIDEO寄存器设置
     * bit[13]:    1   使能VIDEO PLL时钟
     * bit[20:19]  2  设置postDivider为1分频
     * bit[6:0] : 32  设置loopDivider寄存器
     */
    CCM_ANALOG->PLL_VIDEO = (2 << 19) | (1 << 13) | (loopDiv << 0);

    /*
     * MISC2寄存器设置
     * bit[31:30]: 0  VIDEO的post-div设置，时钟源来源于postDivider，1分频
     */
    CCM_ANALOG->MISC2 &= ~(3 << 30);
    CCM_ANALOG->MISC2 = 0 << 30;

    /* LCD时钟源来源与PLL5，也就是VIDEO           PLL  */
    CCM->CSCDR2 &= ~(7 << 15);
    CCM->CSCDR2 |= (2 << 15); /* 设置LCDIF_PRE_CLK使用PLL5 */

    /* 设置LCDIF_PRE分频 */
    CCM->CSCDR2 &= ~(7 << 12);
    CCM->CSCDR2 |= (prediv - 1) << 12; /* 设置分频  */

    /* 设置LCDIF分频 */
    CCM->CBCMR &= ~(7 << 23);
    CCM->CBCMR |= (div - 1) << 23;

    /* 设置LCD时钟源为LCDIF_PRE时钟 */
    CCM->CSCDR2 &= ~(7 << 9); /* 清除原来的设置		 	*/
    CCM->CSCDR2 |= (0 << 9);  /* LCDIF_PRE时钟源选择LCDIF_PRE时钟 */
}
