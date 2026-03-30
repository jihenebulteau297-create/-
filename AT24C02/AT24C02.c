#include "AT24C02.h"


void AT24C02_WriteByte(unsigned char dizhi,Data)//在地址写Data
{
	I2C_Start();
	I2C_SendByte(AT24C02_dizhi);
	I2C_ReceiveAck();
	I2C_SendByte(dizhi);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
}

unsigned char AT24C02_ReadByte(unsigned char dizhi)//在地址读
{
	unsigned char Data;
	
	I2C_Start();
	I2C_SendByte(AT24C02_dizhi);
	I2C_ReceiveAck();
	I2C_SendByte(dizhi);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(AT24C02_dizhi|0x01);
	I2C_ReceiveAck();
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	
	return Data;
}

