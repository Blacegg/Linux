#ifndef __BSP_KEY__
#define __BSP_KEY__

#include "imx6ul.h"
#include "bsp_gpio.h"
#include "bsp_delay.h"

enum Key_Value
{
    KEY_NONE = 0,
    KEY0_VALUE,
};

void Key_Init(void);
int Key_GetValue(void);

#endif
