#include "Timer.h"

void Timer0_Init()
{
	TMOD&=0xf0;
	TMOD|=0x01;
	TF0=0;
	TR0=1;
	TL0=0x18;		
	TH0=0xfc;
	ET0=1;
	EA=1;
	PT0=0;
}

/*
void Timer0_Routine() interrupt 1
{
	static unsigned int num=0;
	TL0=0x66;		
	TH0=0xFC;
	num++;
	if(num>=1000)
	{
		num=0;
		
	}
}
*/
