#include "bsp_delay.h"

/*
 * @description : ��ʱ����ʱ����
 * @param - n : Ҫ��ʱѭ������(�ղ���ѭ��������ģʽ��ʱ)
 * @return : ��
 */

void delay_short(volatile unsigned int n)
{
    while (n--)
    {
    }
}

/*
 * @description : ��ʱ����,�� 396Mhz ����Ƶ��
 * ��ʱʱ���ԼΪ 1ms
 * @param - n : Ҫ��ʱ�� ms ��
 * @return : ��
 */
void delay(volatile unsigned int n)
{
    while (n--)
    {
        delay_short(0x7ff);
    }
}
