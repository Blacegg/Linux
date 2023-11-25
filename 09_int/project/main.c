#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_gpio.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_exit.h"

int main()
{
    unsigned char led_state = OFF;

    int_init();
    clk_init();
    clk_enable();
    led_init();
    beep_init();
    Key_Init();
    EXIT_Init();

    while (1)
    {
        led_state = !led_state;
        led_switch(LED0, led_state);
        delay(500);
    }
    return 0;
}