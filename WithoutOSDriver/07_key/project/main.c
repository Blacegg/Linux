#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_gpio.h"
#include "bsp_key.h"

int main()
{
    int i = 0;
    int keyvalue = 0;
    unsigned char led_state = OFF;
    unsigned char beep_state = OFF;
    clk_enable();
    led_init();
    beep_init();
    Key_Init();

    while (1)
    {
        keyvalue = Key_GetValue();
        if (keyvalue)
        {
            switch (keyvalue)
            {
            case KEY0_VALUE:
                beep_state = !beep_state;
                beep_switch(beep_state);
                break;
            }
        }
        if (i >= 50)
        {
            led_state = !led_state;
            led_switch(LED0, led_state);
            i = 0;
        }
        i++;

        delay(10);
    }

    return 0;
}
