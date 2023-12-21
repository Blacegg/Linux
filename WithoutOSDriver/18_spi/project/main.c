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
#include "bsp_icm20608.h"
#include "bsp_spi.h"

void ShowMenu();
void Case_1();
void Case_2();
void Case_3();
void imx6ul_hardfpu_enable(void);

/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	unsigned char state = OFF;

	imx6ul_hardfpu_enable();
	int_init();		 /* 初始化中断(一定要最先调用！) */
	imx6u_clkinit(); /* 初始化系统时钟 			*/
	delay_init();	 /* 初始化延时 			*/
	clk_enable();	 /* 使能所有的时钟 			*/
	led_init();		 /* 初始化led 			*/
	beep_init();	 /* 初始化beep	 		*/
	uart_init();	 /* 初始化串口，波特率115200 */

	while (icm20608_init())
	{
		state = !state;
		led_switch(LED0, state);
		delayms(500);
	}

	while (1)
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
		// case 3:
		// 	Case_3();
		// 	break;
		default:
			break;
		}
	}

	while (0)
	{
		icm20608_getdata();
		printf("old data:\r\n");
	}
	return 0;
}

void imx6ul_hardfpu_enable(void)
{
	uint32_t cpacr;
	uint32_t fpexc;

	cpacr = __get_CPACR();
	cpacr = (cpacr & ~(CPACR_ASEDIS_Msk | CPACR_D32DIS_Msk)) |
			(3UL << CPACR_cp10_Pos) | (3UL << CPACR_cp11_Pos);
	__set_CPACR(cpacr);
	fpexc = __get_FPEXC();
	fpexc |= 0x40000000UL;
	__set_FPEXC(fpexc);
}

void ShowMenu()
{
	printf("******************************************\r\n");
	printf("********        1.Old Data        ********\r\n");
	printf("********        2.New Data        ********\r\n");
	// printf("********        3.Cycle           ********\r\n");
	printf("******************************************\r\n");
}

void Case_1()
{
	printf("accel x: %d\taccel y %d\taccel z: %d\r\n",
		   icm20608_dev.accel_x_adc, icm20608_dev.accel_y_adc, icm20608_dev.accel_z_adc);
	printf("gyro x: %d\tgyro y %d\tgyro z: %d\r\n",
		   icm20608_dev.gyro_x_adc, icm20608_dev.gyro_y_adc, icm20608_dev.gyro_z_adc);
	printf("temp : %d\r\n", icm20608_dev.temp_adc);
}

void Case_2()
{
	printf("accel x: %d\taccel y %d\taccel z: %d\r\n",
		   icm20608_dev.accel_x_act, icm20608_dev.accel_y_act, icm20608_dev.accel_z_act);
	printf("gyro x: %d\tgyro y %d\tgyro z: %d\r\n",
		   icm20608_dev.gyro_x_act, icm20608_dev.gyro_y_act, icm20608_dev.gyro_z_act);
	printf("temp : %d\r\n", icm20608_dev.temp_act);
}

void Case_3()
{
	while (1)
	{
		Case_2();
		delayms(5000);
	}
}