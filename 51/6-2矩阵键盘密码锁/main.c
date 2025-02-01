#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int Password,Count;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	while(1)
	{
		KeyNum = MatrixKey();
		if(KeyNum)
		{
			if(KeyNum <= 10)
			{
				if(Count < 4)
				{
					LCD_ShowString(1,14,"   ");		//更新显示
					Password*= 10;							//密码左移一位
					Password+= KeyNum % 10;			//获取一位密码
					Count++;										//计次加一
				}
				
				LCD_ShowNum(2,1,Password,4);		//更新显示
			}
			if(KeyNum == 11)									//如果S11按下，确认
			{
				if(Password == 2345)
				{
					LCD_ShowString(1,14,"OK ");		//显示OK
					Count = 0;										//计次清零
					Password = 0;
					LCD_ShowNum(2,1,Password,4);	//更新显示
				}
				else
				{
					LCD_ShowString(1,14,"ERR");
					Count = 0;										//计次清零
					Password = 0;
					LCD_ShowNum(2,1,Password,4);	//更新显示
				}
			}
			if(KeyNum == 12)//如果S12按下，取消
			{
					Count = 0;										//计次清零
					Password = 0;
					LCD_ShowNum(2,1,Password,4);	//更新显示
					LCD_ShowString(1,14,"   ");		//更新显示
			}
		}
	}
}