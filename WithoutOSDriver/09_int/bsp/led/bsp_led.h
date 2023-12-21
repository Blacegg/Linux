#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "imx6ul.h"
#include "bsp_gpio.h"

#define LED0 0

/* º¯ÊıÉùÃ÷ */
void led_init(void);
void led_switch(int led, int status);

#endif