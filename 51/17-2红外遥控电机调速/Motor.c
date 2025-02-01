#include <REGX52.H>
#include "Timer1.h"

sbit Motor=P1^0;

unsigned char Counter,Compare;

/**
  * @brief 电机初始化
  * @param  无
  * @retval 无
  */

void Motor_Init()
{
	Timer1_Init();
}

/**
  * @brief 设定电机速度
  * @param  电机速度
  * @retval 无
  */

void Motor_SetSpeed(unsigned char Speed)
{
	Compare=Speed;
}

void Timer1_Rountine() interrupt 3
{
	TL1 = 0xA4;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
	Counter++;
	if(Counter>=100) Counter=0;
	if(Counter<Compare)
	{
		Motor=1;
	}
	else
	{
		Motor=0;
	}
}