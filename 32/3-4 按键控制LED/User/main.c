#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint8_t KeyNum;

int main(void)
{
	LED_Init();	//初始化LED
	Key_Init();	//初始化按键
	
	while(1)
	{
		KeyNum = Key_GetNum();	//获取键码
		if(KeyNum == 1)	//如果按键1按下
		{
			LED1_Turn();	//反转LED1状态
		}
		if(KeyNum == 2)	//如果按键2按下
		{
			LED2_Turn();	//反转LED2状态
		}
	}
}
