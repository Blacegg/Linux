#ifndef __BSP_GPIO__
#define __BSP_GPIO__

#include "imx6ul.h"

typedef enum
{
    kGPIO_DigitalInput = 0U,
    kGPIO_DigitalOutput = 1U,
} GPIO_Pin_Direction_t;

typedef struct
{
    GPIO_Pin_Direction_t Direction;
    uint8_t OutputLogic;
} GPIO_Pin_Config_t;

void GPIO_Init(GPIO_Type *base, int pin, GPIO_Pin_Config_t *config);
int GPIO_PinRead(GPIO_Type *base, int pin);
void GPIO_PinWrite(GPIO_Type *base, int pin, int value);

#endif