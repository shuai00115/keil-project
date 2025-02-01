#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"

unsigned char KeyNum,MODE,TimeSetSelect,TimeSetFlashFlag;

/**
  * @brief LCD1602显示时间
  * @param  无
  * @retval 无
  */

void TimeShow(void)
{
		DS1302_ReadTime();
		LCD_ShowNum(1,1,DS1302_Time[0],2);
		LCD_ShowNum(1,4,DS1302_Time[1],2);
		LCD_ShowNum(1,7,DS1302_Time[2],2);
		LCD_ShowNum(2,1,DS1302_Time[3],2);
		LCD_ShowNum(2,4,DS1302_Time[4],2);
		LCD_ShowNum(2,7,DS1302_Time[5],2);
}

/**
  * @brief LCD1602设置时间
  * @param  无
  * @retval 无
  */

void TimeSet(void)
{
	//当按下按键2时进入选择模式，选择要调整的数据
	if(KeyNum==2)
	{
		TimeSetSelect++;
		TimeSetSelect%=6;
	}
	//当按下按键3时，对当前数据进1
	if(KeyNum==3)
	{
		DS1302_Time[TimeSetSelect]++;
		//对年的范围进行判断
		if(DS1302_Time[0]>99){DS1302_Time[0]=0;}
		//对月的范围进行判断
		if(DS1302_Time[1]>12){DS1302_Time[1]=1;}
		//对日的范围进行判断
		if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7||
			 DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}//大月则31天再归零
		}
		else if(DS1302_Time[1]==4||DS1302_Time[1]==6||DS1302_Time[1]==9||DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}//小月则30天再归零
		}
		else if(DS1302_Time[1]==2)//二月则再对闰年进行判断
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}//如果是闰年。则29天再归零
			}
			else 
			{
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}//如果不是闰年。则29天再归零
			}
		}
		//对时的范围进行判断
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;}
		//对分的范围进行判断
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;}
		//对秒的范围进行判断
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;}
	}
	//当按下按键4时，对当前数据退1
	if(KeyNum==4)
	{
		DS1302_Time[TimeSetSelect]--;
		//对年的范围进行判断
		if(DS1302_Time[0]<0){DS1302_Time[0]=99;}
		//对月的范围进行判断
		if(DS1302_Time[1]<1){DS1302_Time[1]=12;}
		//对日的范围进行判断
		if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7||
			 DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=31;}
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==4||DS1302_Time[1]==6||DS1302_Time[1]==9||DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=30;}
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=29;}
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			}
			else 
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=28;}
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
		}
		//对时的范围进行判断
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;}
		//对分的范围进行判断
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;}
		//对秒的范围进行判断
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;}
	}
	//当选择时让被选中的数据闪烁
	if(TimeSetFlashFlag==1&&TimeSetSelect==0){LCD_ShowString(1,1,"  ");}
	else{LCD_ShowNum(1,1,DS1302_Time[0],2);}
	if(TimeSetFlashFlag==1&&TimeSetSelect==1){LCD_ShowString(1,4,"  ");}
	else{LCD_ShowNum(1,4,DS1302_Time[1],2);}
	if(TimeSetFlashFlag==1&&TimeSetSelect==2){LCD_ShowString(1,7,"  ");}
	else{LCD_ShowNum(1,7,DS1302_Time[2],2);}
	if(TimeSetFlashFlag==1&&TimeSetSelect==3){LCD_ShowString(2,1,"  ");}
	else{LCD_ShowNum(2,1,DS1302_Time[3],2);}
	if(TimeSetFlashFlag==1&&TimeSetSelect==4){LCD_ShowString(2,4,"  ");}
	else{LCD_ShowNum(2,4,DS1302_Time[4],2);}
	if(TimeSetFlashFlag==1&&TimeSetSelect==5){LCD_ShowString(2,7,"  ");}
	else{LCD_ShowNum(2,7,DS1302_Time[5],2);}

}	


void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0Init();
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	
	DS1302_SetTime();
	
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)
		{
			if(MODE==0) {MODE=1;TimeSetSelect=0;}
			else if(MODE==1) {MODE=0;DS1302_SetTime();}
		}
		switch(MODE)
		{
			case 0:TimeShow();break;
			case 1:TimeSet();break;
		}

	}
}

void Timer0_Rountine() interrupt 1
{
	static unsigned int T0Count = 0;
	TH0 = 0xFC;
	TL0 = 0x66;
	T0Count++;
	if(T0Count >= 500)
	{
		T0Count = 0;
		TimeSetFlashFlag=!TimeSetFlashFlag;
	}
}