#include <REGX52.H>
#include "Delay.h"

unsigned char Key_KeyNum;

unsigned char Key(void)
{
	unsigned char Temp;
	Temp=Key_KeyNum;
	Key_KeyNum=0;
	return Temp;
}

/**
  * @brief 获取独立按键的键码
  * @param  无
  * @retval 按下按键的键码，范围：0~4，无按键按下时返回值为0
  */

unsigned char Key_GetState()
{
	unsigned char KeyNumber = 0;
	
	if(P3_1 == 0){KeyNumber = 1;}
	if(P3_0 == 0){KeyNumber = 2;}
	if(P3_2 == 0){KeyNumber = 3;}
	if(P3_3 == 0){KeyNumber = 4;}
	
	return KeyNumber;
}

void Key_Loop(void)
{
	static unsigned char NowState,LastState;
	LastState=NowState;
	NowState=Key_GetState();
	if(LastState==1&&NowState==0)
	{
		Key_KeyNum=1;
	}
	if(LastState==2&&NowState==0)
	{
		Key_KeyNum=2;
	}
	if(LastState==3&&NowState==0)
	{
		Key_KeyNum=3;
	}
	if(LastState==4&&NowState==0)
	{
		Key_KeyNum=4;
	}
}