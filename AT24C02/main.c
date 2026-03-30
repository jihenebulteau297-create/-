#include <REGX52.H>
#include "UART.h"
#include "Delay.h"
#include "Key.h"
#include "AT24C02.h"


unsigned char num0,baocun;
unsigned char keynum;


void UART_Routine() interrupt 4
{
	if(RI==1){							//判断是负有数据传进来
		UART_SendByte(SBUF);				
		num0=SBUF;						//中间值
		AT24C02_WriteByte(0,num0);		//往AT24C02的地址0写传进来的数据
		Delay(5);						//等数据完全写好
		RI=0;							//允许下次串口发数据进来
	}
}


void main(){
	
	UART_Init();						//初始化串口
	
	
	while(1){
		keynum=Key();					//扫描按键
		
		if(keynum==3){					//如果按了按键3
			baocun=AT24C02_ReadByte(0);	//读取AT24C02的地址0里的数据
			UART_SendByte(baocun);		//往电脑发送上次传进来的数据
		}
	}
}
