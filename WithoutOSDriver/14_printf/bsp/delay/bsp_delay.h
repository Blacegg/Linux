#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

#include "imx6ul.h"
#include "bsp_int.h"
#include "bsp_led.h"

void Delay_Init(void);
void Delay_us(unsigned int usdelay);
void Delay_ms(unsigned int msdelay);
void delay(volatile unsigned int n);
void GPT1_IrqHandler(void);

#endif