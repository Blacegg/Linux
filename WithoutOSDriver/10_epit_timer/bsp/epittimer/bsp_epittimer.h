#ifndef __BSP_EPITTIMER__
#define __BSP_EPITTIMER__

#include "imx6ul.h"

void EPIT_Init(unsigned int frac, unsigned int value);
void EPIT_IrqHandler(void);

#endif