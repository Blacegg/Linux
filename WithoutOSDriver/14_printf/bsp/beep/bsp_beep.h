#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

#include "imx6ul.h"
#include "bsp_gpio.h"

/* �������� */
void beep_init(void);
void beep_switch(int status);

#endif