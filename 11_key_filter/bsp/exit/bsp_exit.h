#ifndef __BSP_EXIT__
#define __BSP_EXIT__

#include "imx6ul.h"

void EXIT_Init(void);             /* 中断初始化 */
void GPIO1_IO18_IrqHandler(void); /* 中断处理函数 */

#endif