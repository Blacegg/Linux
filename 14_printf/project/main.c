#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_uart.h"
#include "stdio.h"

int main()
{
    int a, b;
    unsigned char state = OFF;

    int_init();
    clk_init();
    clk_enable();
    led_init();
    beep_init();
    Delay_Init();
    UART_Init();

    while (1)
    {
        printf("输入两个整数，使用空格隔开：");
        scanf("%d %d", &a, &b);
        printf("\r\n数据 %d + %d = %d\r\n\r\n", a, b, a + b);

        state = !state;
        led_switch(LED0, state);
    }
    return 0;
}