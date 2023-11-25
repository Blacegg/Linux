#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_uart.h"

int main()
{
    unsigned char a = 0;
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
        puts("请输入一个字符：");
        a = getc();
        putc(a);
        puts("\r\n");

        puts("您输入的字符为：");
        putc(a);
        puts("\r\n\r\n");

        state = !state;
        led_switch(LED0, state);
    }
    return 0;
}