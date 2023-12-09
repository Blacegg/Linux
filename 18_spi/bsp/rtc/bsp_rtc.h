#ifndef __BSP_RTC__
#define __BSP_RTC__

#include "imx6ul.h"

#define SECONDS_IN_A_DAY (86400)
#define SECONDS_IN_A_HOUR (3600)
#define SECONDS_IN_A_MINUTE (60)
#define DAYS_IN_A_YEAR (365)
#define YEAR_RANGE_START (1970)
#define YEAR_RANGE_END (2099)

struct RTC_DateTime
{
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
};

void RTC_Init();
void RTC_Enable();
void RTC_Disenable();
unsigned int RTC_Coverdate_to_Seconds(struct RTC_DateTime *datetime);
unsigned int RTC_GetSeconds();
void RTC_SetDateTime(struct RTC_DateTime *datetime);
void RTC_GetDateTime(struct RTC_DateTime *datetime);

#endif