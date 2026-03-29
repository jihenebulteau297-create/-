#include <REGX52.H>
#include "Timer.h"

#define MAX_TASKS 2 //表示有两个任务
#define MAX_TASK_DEP 32//表示栈的深度
#define guaqi 0		//挂起态
#define yunxing 1		//运行态



unsigned char idata task_sp[MAX_TASKS];//任务的堆栈指针（存任务的）
unsigned char idata task_stack[MAX_TASKS][MAX_TASK_DEP];//每个task任务的堆栈
unsigned char task_id;//当前任务号
unsigned int time[2];		//未来时间
unsigned char zhuangtai[2]={1,1};		//记录LED状态				

void Delay(unsigned int ms);		
void task_switch(void);
void task0(void);
void task1(void);
void task_load(unsigned int fn,unsigned char tid);

volatile unsigned int num;

void main()
{	  
	  Timer0_Init();
	  task_load(task0,0);
	  task_load(task1,1);
	  task_id = 0;
	  P2_7=0;
	  P2_0=0;
	  SP=task_sp[0];
	  task_switch();
}



void task_switch()
{
   task_sp[task_id]=SP;
	
	task_id=task_id+1;
	if(task_id==MAX_TASKS)
	{
	  task_id=0;
	}
	SP=task_sp[task_id];
}

void task0()
{
	
  while(1)
	{
		Delay(1000);
		P2_0=~P2_0;
		task_switch();
	}
}

void task1()
{
	
  while(1)
	{
		Delay(500);
		P2_7=~P2_7;
		task_switch();
	}
}
	
void task_load(unsigned int fn,unsigned char tid)
{
  //task_sp[tid]=  task_stack[tid]+1;//跳到下一个任务
	task_stack[tid][1] = (unsigned char)(fn >> 8); 
  task_stack[tid][0] = (unsigned char)fn;
	task_sp[tid] = (unsigned char)&task_stack[tid][1];
}



void Timer0_Routine() interrupt 1
{
	TL0=0x18;		
	TH0=0xfc;
	
	num++;
}

void Delay(unsigned int ms)
{
	if(zhuangtai[task_id]==1)		//判断状态
		{
			time[task_id]=num+ms;		//计算延迟结束时间
			zhuangtai[task_id]=0;		//反转状态
		}
		while(zhuangtai[task_id] == 0){		//方便延迟结束是可以不跳回中转函数
		if(num>=time[task_id])		//是否到达延迟结束时间
			{
				zhuangtai[task_id]=1;		//反转状态
				break;		//回LED函数			
			}
		task_switch();		//回中转函数
	}
}
