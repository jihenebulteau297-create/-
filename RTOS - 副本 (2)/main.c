#include <REGX52.H>
#include "Timer.h"


#define TASK_NUM 2 //表示有两个任务


typedef enum{
	guaqi=0, 		//挂起态
	yunxing 		//运行态
} task_state_t;		

typedef struct {
    void (*task_func)(void);		//存放任务函数地址		
    unsigned int delay;				//存放时停时间
    task_state_t state;				//表示状态
} task_t;							


task_t tasks[TASK_NUM];			//两个数组结构				
volatile unsigned int num;		//一秒加1
			

void Timer0_Routine() interrupt 1		//中断
{
	static char i=0;
	TL0=0x18;		//一毫秒
	TH0=0xfc;		//定时
	
	num++;
	for(i=0;i<TASK_NUM;i++){
		if(tasks[i].state==guaqi){		//判断状态
			if(tasks[i].delay>0){		//判断是否还有时停时间
				tasks[i].delay--;
			}
			if(tasks[i].delay==0){		//判断时停是否消耗完
				tasks[i].state = yunxing;		//改变状态
			}
		}
	}
}


void task_delay(unsigned char i,unsigned int ms)		//根据传过来的i和ms决定哪个任务时停多长
{
	tasks[i].delay = ms;		//i任务时停ms
	tasks[i].state = guaqi;		//改变任务i状态
}


void task_switch(void){
	static char i=0;
	for(i=0;i<TASK_NUM;i++){
		if(tasks[i].state == yunxing && tasks[i].delay == 0){		//判断判断时停是否消耗完且为待命态
			tasks[i].task_func();		//执行任务i
		}
	}
}


void task0()
{
	P2_0=~P2_0;
	task_delay(0,1000);
}

void task1()
{
	P2_2=~P2_2;
	task_delay(1,500);
}


void task_Init(){		//定义任务
	tasks[0].task_func = task0;
    tasks[0].delay = 0;
    tasks[0].state = yunxing;

    tasks[1].task_func = task1;
    tasks[1].delay = 0;
    tasks[1].state = yunxing;
}


void main()
{	  
	Timer0_Init();
	task_Init();	
	
	while(1){
		task_switch();
	}
}



