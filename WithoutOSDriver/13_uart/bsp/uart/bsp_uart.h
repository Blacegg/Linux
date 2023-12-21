#ifndef __BSP_UART__
#define __BSP_UART__

#include "imx6ul.h"

void UART_Init(void);
void UART_IO_Init(void);
void UART_Enable(UART_Type *base);
void UART_Disable(UART_Type *base);
void UART_SoftReset(UART_Type *base);
void UART_SetBaudrate(UART_Type *base,
                      unsigned int baudrate,
                      unsigned int srcclock_hz);
void putc(unsigned char c);
void puts(char *str);
unsigned char getc(void);
void raise(int sig_nr);

#endif