#ifndef __BSP_AP3216C__
#define __BSP_AP3216C__

#include "imx6ul.h"

#define AP3216C_ADDR 0X1E

#define AP3216C_SYSTEMCONG 0X00
#define AP3216C_INTSTATUS 0X01
#define AP3216C_INTCLEAR 0X02
#define AP3216C_IRDATALOW 0X0A
#define AP3216C_IRDATAHIGH 0X0B
#define AP3216C_ALSDATALOW 0X0C
#define AP3216C_ALSDATAHIGH 0X0D
#define AP3216C_PSDATALOW 0X0E
#define AP3216C_PSDATAHIGH 0X0F

unsigned char ap3216c_init(void);
unsigned char ap3216c_readonebyte(unsigned char addr,
                                  unsigned char reg);
unsigned char ap3216c_writeonebyte(unsigned char addr,
                                   unsigned char reg,
                                   unsigned char data);
void ap3216c_readdata(unsigned short *ir, unsigned short *ps, unsigned short *als);

#endif
