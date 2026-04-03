#include <REGX51.H>								
#include <oled.h>									//OLED库函数

#define uchar unsigned char				//用uchar 表示 unsigned char类型
#define uint unsigned int					//用uint 表示 unsigned int类型


extern uchar code BMPclr[];				//图片清屏用
extern uchar code BMP0[];					//oledfont.h中，图片0取模数组，做外部变量声明（如用到更多图片，均需要声明）
extern uchar code BMP1[];					//oledfont.h中，图片0取模数组，做外部变量声明（如用到更多图片，均需要声明）
extern uchar code BMP2[];
extern uchar code BMP3[];
extern uchar code BMP4[];



void main(void)
{	
	OLED_Init();										//初始化OLED  
	OLED_Clear();										//清空屏幕
	
	while(1) 
	{	
//		OLED_DrawBMP_Faster(0,0,76,7,BMP3);
//		OLED_DrawBMP_Faster(0,0,76,7,BMP2);
		BMPmove(93,1,128,4,BMP2,LEFT,1);		//
		BMPmove(93,1,128,4,BMP3,LEFT,1);		//doge向左跑
		BMPmove(93,1,128,4,BMP4,LEFT,1);		//
//		BMPmove(64,1,128,7,BMP2,LEFT,0);
		
		
	}
}

