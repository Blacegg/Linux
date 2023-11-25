#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_gpio.h"
#include "bsp_key.h"

int main()
{
    int keyvalue = 0;
    //int ledvalue = 0;
    unsigned char led_state = OFF;
    unsigned char beep_state = OFF;
    clk_enable();
    led_init();
    beep_init();
    Key_Init();
    clk_init();

    while (1)
    {
        keyvalue = Key_GetValue();
        if (keyvalue)
        {
            beep_state = !beep_state;
            beep_switch(beep_state);
        }

        led_state = !led_state;
        led_switch(LED0, led_state);
        delay(500);
    }

    return 0;
}
