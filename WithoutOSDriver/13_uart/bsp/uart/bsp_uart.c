#include "bsp_uart.h"

void UART_Init(void)
{
    UART_IO_Init();
    UART_Disable(UART1);
    UART_SoftReset(UART1);

    UART1->UCR1 = 0;
    UART1->UCR1 &= ~(1 << 14);

    UART1->UCR2 |= ((1 << 14) | (1 << 5) | (1 << 2) | (1 << 1));
    UART1->UCR3 |= (1 << 2);

    UART1->UFCR = (5 << 7);
    UART1->UBIR = 71;
    UART1->UBMR = 3124;

#if 0

    UART_SetBaudrate(UART1, 115200, 80000000);

#endif

    UART_Enable(UART1);
}

void UART_IO_Init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0X10B0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0X10B0);
}

void UART_SetBaudrate(UART_Type *base,
                      unsigned int baudrate,
                      unsigned int srcclock_hz)
{
    uint32_t numerator = 0U;
    uint32_t denominator = 0U;
    uint32_t divisor = 0U;
    uint32_t refFreqDiv = 0U;
    uint32_t divider = 1U;
    uint64_t baudDiff = 0U;
    uint64_t tempNumerator = 0U;
    uint32_t tempDenominator = 0U;

    numerator = srcclock_hz;
    denominator = baudrate << 4;
    divisor = 1;

    while (denominator != 0)
    {
        divisor = denominator;
        denominator = numerator % denominator;
        numerator = divisor;
    }
    numerator = srcclock_hz / divisor;
    denominator = (baudrate << 4) / divisor;

    /* numerator ranges from 1 ~ 7 * 64k */
    /* denominator ranges from 1 ~ 64k */
    if ((numerator > (UART_UBIR_INC_MASK * 7)) || (denominator > UART_UBIR_INC_MASK))
    {
        uint32_t m = (numerator - 1) / (UART_UBIR_INC_MASK * 7) + 1;
        uint32_t n = (denominator - 1) / UART_UBIR_INC_MASK + 1;
        uint32_t max = m > n ? m : n;
        numerator /= max;
        denominator /= max;
        if (0 == numerator)
        {
            numerator = 1;
        }
        if (0 == denominator)
        {
            denominator = 1;
        }
    }
    divider = (numerator - 1) / UART_UBIR_INC_MASK + 1;

    switch (divider)
    {
    case 1:
        refFreqDiv = 0x05;
        break;
    case 2:
        refFreqDiv = 0x04;
        break;
    case 3:
        refFreqDiv = 0x03;
        break;
    case 4:
        refFreqDiv = 0x02;
        break;
    case 5:
        refFreqDiv = 0x01;
        break;
    case 6:
        refFreqDiv = 0x00;
        break;
    case 7:
        refFreqDiv = 0x06;
        break;
    default:
        refFreqDiv = 0x05;
        break;
    }
    /* Compare the difference between baudRate_Bps and calculated baud rate.
     * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)).
     * baudDiff = (srcClock_Hz/divider)/( 16 * ((numerator / divider)/ denominator).
     */
    tempNumerator = srcclock_hz;
    tempDenominator = (numerator << 4);
    divisor = 1;
    /* get the approximately maximum divisor */
    while (tempDenominator != 0)
    {
        divisor = tempDenominator;
        tempDenominator = tempNumerator % tempDenominator;
        tempNumerator = divisor;
    }
    tempNumerator = srcclock_hz / divisor;
    tempDenominator = (numerator << 4) / divisor;
    baudDiff = (tempNumerator * denominator) / tempDenominator;
    baudDiff = (baudDiff >= baudrate) ? (baudDiff - baudrate) : (baudrate - baudDiff);
    if (baudDiff < (baudrate / 100) * 3)
    {
        base->UFCR &= ~UART_UFCR_RFDIV_MASK;
        base->UFCR |= UART_UFCR_RFDIV(refFreqDiv);
        base->UBIR = UART_UBIR_INC(denominator - 1);
        base->UBMR = UART_UBMR_MOD(numerator / divider - 1);
    }
}

void UART_Enable(UART_Type *base)
{
    base->UCR1 |= (1 << 0);
}

void UART_Disable(UART_Type *base)
{
    base->UCR1 &= ~(1 << 0);
}

void UART_SoftReset(UART_Type *base)
{
    base->UCR2 &= ~(1 << 0);
    while (((base->UCR2) & 0X1) == 0)
    {
    };
}

void putc(unsigned char c)
{
    while ((((UART1->USR2) >> 3) & 0X1) == 0)
    {
    };
    UART1->UTXD = c & 0XFF;
}

void puts(char *str)
{
    char *p = str;
    while (*p)
        putc(*p++);
}

unsigned char getc(void)
{
    while (((UART1->USR2) & 0X1) == 0)
    {
    };
    return UART1->URXD;
}

void raise(int sig_nr)
{
}