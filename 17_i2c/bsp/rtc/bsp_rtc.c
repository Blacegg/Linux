#include "bsp_rtc.h"
#include "stdio.h"

void RTC_Init()
{
    SNVS->HPCOMR |= (1 << 31);
#if 0
    struct RTC_DateTime rtcdate;
    rtcdate.year = 2018U;
    rtcdate.month = 12U;
    rtcdate.day = 13U;
    rtcdate.hour = 14U;
    rtcdate.minute = 52;
    rtcdate.second = 0;
    RTC_SetDateTime(&rtcdate);
#endif
    RTC_Enable();
}

void RTC_Enable()
{
    SNVS->LPCR |= (1 << 0);
    while (!((SNVS->LPCR) & 0X01))
    {
    }
}

void RTC_Disenable()
{
    SNVS->LPCR &= ~(1 << 0);
    while ((SNVS->LPCR) & 0X01)
    {
    }
}

unsigned char RTC_IsLeapYear(unsigned short year)
{
    unsigned char value = 0;

    if (year % 400 == 0)
    {
        value = 1;
    }
    else
    {
        if ((year % 4 == 0) && (year % 100 != 0))
        {
            value = 1;
        }
        else
        {
            value = 0;
        }
    }
    return value;
}

unsigned int RTC_Coverdate_to_Seconds(struct RTC_DateTime *datetime)
{
    unsigned short i = 0;
    unsigned int seconds = 0;
    unsigned int days = 0;
    unsigned short monthdays[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U,
                                  181U, 212U, 243U, 273U, 304U, 334U};

    for (i = 1970; i < datetime->year; i++)
    {
        days += DAYS_IN_A_YEAR;
        if (RTC_IsLeapYear(i))
        {
            days += 1;
        }
    }
    days += monthdays[datetime->month];
    if ((RTC_IsLeapYear(datetime->year)) && (datetime->month >= 3))
    {
        days += 1;
    }
    days += datetime->day - 1;
    seconds = days * SECONDS_IN_A_DAY +
              datetime->hour * SECONDS_IN_A_HOUR +
              datetime->minute * SECONDS_IN_A_MINUTE +
              datetime->second;

    return seconds;
}

void RTC_SetDateTime(struct RTC_DateTime *datetime)
{
    unsigned int seconds = 0;
    unsigned int tmp = SNVS->LPCR;
    RTC_Disenable();
    seconds = RTC_Coverdate_to_Seconds(datetime);
    SNVS->LPSRTCMR = (unsigned int)(seconds >> 17);
    SNVS->LPSRTCLR = (unsigned int)(seconds << 15);
    if (tmp & 0x1)
    {
        RTC_Enable();
    }
}

void RTC_ConvertSeconds_to_Datetime(unsigned int seconds,
                                    struct RTC_DateTime *datetime)
{
    unsigned int x;
    unsigned int seconds_remaining, days;
    unsigned short days_in_year;
    unsigned char days_permonth[] = {0U, 31U, 28U, 31U, 30U, 31U,
                                     30U, 31U, 31U, 30U, 31U, 30U, 31U};
    seconds_remaining = seconds;
    days = seconds_remaining / SECONDS_IN_A_DAY;
    seconds_remaining = seconds_remaining % SECONDS_IN_A_DAY;

    datetime->hour = seconds_remaining / SECONDS_IN_A_HOUR;
    seconds_remaining = seconds_remaining % SECONDS_IN_A_HOUR;
    datetime->minute = seconds_remaining / SECONDS_IN_A_MINUTE;
    seconds_remaining = seconds_remaining % SECONDS_IN_A_MINUTE;
    datetime->minute = seconds_remaining;

    days_in_year = DAYS_IN_A_YEAR;
    datetime->year = YEAR_RANGE_START;
    while (days > DAYS_IN_A_YEAR)
    {
        datetime->year += 1;
        days -= days_in_year;
        if (RTC_IsLeapYear(datetime->year))
        {
            days_in_year = DAYS_IN_A_YEAR + 1;
        }
        else
        {
            days_in_year = DAYS_IN_A_YEAR;
        }
    }
    if (RTC_IsLeapYear(datetime->year))
    {
        days_permonth[2] = 29;
    }
    for (x = 1; x <= 12; x++)
    {
        if (days <= days_permonth[x])
        {
            datetime->month = x;
            break;
        }
        else
        {
            days -= days_permonth[x];
        }
    }
    datetime->day = days;
}

unsigned int RTC_GetSeconds()
{
    unsigned int seconds = 0;

    seconds = (SNVS->LPSMCMR << 17) | (SNVS->LPSRTCLR >> 15);
    return seconds;
}

void RTC_GetDateTime(struct RTC_DateTime *datetime)
{
    unsigned int seconds = 0;
    seconds = RTC_GetSeconds();
    RTC_ConvertSeconds_to_Datetime(seconds, datetime);
}