#include "bsp_delay.h"

/*
 * @description : 短时间延时函数
 * @param - n : 要延时循环次数(空操作循环次数，模式延时)
 * @return : 无
 */

void delay_short(volatile unsigned int n)
{
    while (n--)
    {
    }
}

/*
 * @description : 延时函数,在 396Mhz 的主频下
 * 延时时间大约为 1ms
 * @param - n : 要延时的 ms 数
 * @return : 无
 */
void delay(volatile unsigned int n)
{
    while (n--)
    {
        delay_short(0x7ff);
    }
}
