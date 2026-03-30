#include <REGX52.H>
#include "UART.h"
#include "Delay.h"
#include "Key.h"
#include "AT24C02.h"


unsigned char num0,baocun;
unsigned char keynum;


void UART_Routine() interrupt 4
{
	if(RI==1){
		UART_SendByte(SBUF);
		num0=SBUF;
		AT24C02_WriteByte(0,num0);
		Delay(5);
		RI=0;
	}
}


void main(){
	
	UART_Init();
	
	
	while(1){
		keynum=Key();
		
		if(keynum==3){
			baocun=AT24C02_ReadByte(0);
			UART_SendByte(baocun);
		}
	}
}