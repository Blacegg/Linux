#ifndef __BSP_GPIO__
#define __BSP_GPIO__

#include "imx6ul.h"

typedef enum
{
    kGPIO_DigitalInput = 0U,
    kGPIO_DigitalOutput = 1U,
} GPIO_Pin_Direction_t;

typedef enum _gpio_interrupt_mode
{
    kGPIO_NoIntmode = 0U,              /* 无中断功能 */
    kGPIO_IntLowLevel = 1U,            /* 低电平触发 */
    kGPIO_IntHighLevel = 2U,           /* 高电平触发 */
    kGPIO_IntRisingEdge = 3U,          /* 上升沿触发 */
    kGPIO_IntFallingEdge = 4U,         /* 下降沿触发 */
    kGPIO_IntRisingOrFallingEdge = 5U, /* 上升沿和下降沿都触发 */
} GPIO_Interrupt_Mode_t;

typedef struct
{
    GPIO_Pin_Direction_t Direction;
    uint8_t OutputLogic;
    GPIO_Interrupt_Mode_t interruptMode;
} GPIO_Pin_Config_t;

void GPIO_Init(GPIO_Type *base, int pin, GPIO_Pin_Config_t *config);
int GPIO_PinRead(GPIO_Type *base, int pin);
void GPIO_PinWrite(GPIO_Type *base, int pin, int value);
void GPIO_IntConfig(GPIO_Type *base, unsigned int pin,
                    GPIO_Interrupt_Mode_t pin_int_mode);
void GPIO_EnableInt(GPIO_Type *base, unsigned int pin);
void GPIO_DisableInt(GPIO_Type *base, unsigned int pin);
void GPIO_ClearIntFlags(GPIO_Type *base, unsigned int pin);

#endif