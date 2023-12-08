#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_uart.h"
#include "stdio.h"
#include "bsp_rtc.h"
#include "bsp_ap3216c.h"
#include "bsp_i2c.h"

void ShowMenu();
/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	unsigned short ir, als, ps;
	unsigned char state = OFF;

	int_init();		 /* 初始化中断(一定要最先调用！) */
	imx6u_clkinit(); /* 初始化系统时钟 			*/
	delay_init();	 /* 初始化延时 			*/
	clk_enable();	 /* 使能所有的时钟 			*/
	led_init();		 /* 初始化led 			*/
	beep_init();	 /* 初始化beep	 		*/
	uart_init();	 /* 初始化串口，波特率115200 */
	RTC_Init();

	while (0)
	{
		unsigned char select = 0;
		ShowMenu();
		printf("please input your selection :");
		scanf("%d", &select);
		printf("\r\n");
		switch (select)
		{
		case 1:
			Case_1();
			break;
		case 2:
			Case_2();
			break;
		case 3:
			Case_3();
			break;
		default:
			break;
		}
	}
	while (1)
	{
		while (ap3216c_init())
		{
			state = !state;
			led_switch(LED0, state);
			delayms(500);
		}
		ap3216c_readdata(&ir, &ps, &als);
		printf("ir=%d\tps=%d\tals=%d\r\n", ir, ps, als);
		delayms(500);
	}
	return 0;
}

void ShowMenu()
{
	printf("******************************************\r\n");
	printf("********        1.Set Time        ********\r\n");
	printf("********        2.Get Time        ********\r\n");
	printf("********        3.Cycle           ********\r\n");
	printf("******************************************\r\n");
}

void Case_1()
{
	struct RTC_DateTime datetime;
	printf("please input year:");
	scanf("%d", &datetime.year);
	printf("\r\n");
	printf("please input month:");
	scanf("%d", &datetime.month);
	printf("\r\n");
	printf("please input day:");
	scanf("%d", &datetime.day);
	printf("\r\n");
	printf("please input hour:");
	scanf("%d", &datetime.hour);
	printf("\r\n");
	printf("please input minute:");
	scanf("%d", &datetime.minute);
	printf("\r\n");
	printf("please input second:");
	scanf("%d", &datetime.second);
	printf("\r\n");
	RTC_SetDateTime(&datetime);
	printf("Set Time Successful!\r\n");
}

void Case_2()
{
	struct RTC_DateTime datetime;
	RTC_GetDateTime(&datetime);
	printf("year:%d\n", datetime.year);
	printf("month:%d\n", datetime.month);
	printf("day:%d\n", datetime.day);
	printf("hour:%d\n", datetime.hour);
	printf("minute:%d\n", datetime.minute);
	printf("second:%d\n", datetime.second);
}

void Case_3()
{
	struct RTC_DateTime datetime;
	while (1)
	{
		Case_2();
		delayms(5000);
	}
}