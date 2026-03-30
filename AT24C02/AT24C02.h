#ifndef __AT24C02_H__
#define __AT24C02_H__


#include <REGX52.H>
#include "i2c.h"


#define AT24C02_dizhi 0xa0


void AT24C02_WriteByte(unsigned char zijie,Data);
unsigned char AT24C02_ReadByte(unsigned char zijie);


#endif