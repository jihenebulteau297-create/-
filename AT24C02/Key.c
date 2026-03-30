#include "Key.h"

unsigned char Key()
{
	char unm=0;
	if(P3_1==0){Delay(20);while(P3_1==0);Delay(20);unm=1;}
	if(P3_0==0){Delay(20);while(P3_0==0);Delay(20);unm=2;}
	if(P3_2==0){Delay(20);while(P3_2==0);Delay(20);unm=3;}
	if(P3_3==0){Delay(20);while(P3_3==0);Delay(20);unm=4;}
	
	return unm;
}
