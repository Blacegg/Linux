#ifndef __BSP_KEYFILTER__
#define __BSP_KEYFILTER__

#include "bsp_key.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_beep.h"

void FilterKey_Init(void);
void FilterTimer_Init(unsigned int value);
void FilterTimer_Stop(void);
void FilterTimer_Restart(unsigned int value);
void FilterTimer_IrqHandler(void);
void GPIO1_16_31_IrqHandler(void);

#endif