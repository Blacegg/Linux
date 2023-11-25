#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_gpio.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_exit.h"
#include "bsp_epittimer.h"

int main()
{
    int_init();
    clk_init();
    clk_enable();
    led_init();
    beep_init();
    Key_Init();
    EXIT_Init();
    EPIT_Init(0, 66000000 / 2);

    while (1)
    {
        delay(500);
    }
    return 0;
}