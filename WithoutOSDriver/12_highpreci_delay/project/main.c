#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_gpio.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_exit.h"
#include "bsp_epittimer.h"
#include "bsp_keyfilter.h"

int main()
{
    unsigned char led_state = OFF;

    int_init();
    clk_init();
    clk_enable();
    led_init();
    beep_init();
    Delay_Init();

    while (1)
    {
        led_state = !led_state;
        led_switch(LED0, led_state);
        Delay_ms(1000);
    }
    return 0;
}