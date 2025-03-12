#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/*
**函数：按键初始化
**参数：无
**返回值：无
*/

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//开启GPIOB的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	//设置PB1和PB11引脚为上拉输出
	
}

/*
**函数：获取按键键码
**参数：无
**返回值：按下按键的键码值，范围0~2，0代表无按键按下
*/

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;	//定义变量，默认键码为0
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)	//读取输入寄存器状态，如果为0，则代表按键1按下
	{
		Delay_ms(20);	//延时消抖
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);	//等待按键松手
		Delay_ms(20);	//延时消抖
		KeyNum = 1;		//置键码为1
	}	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)	//读取输入寄存器状态，如果为0，则代表按键2按下
	{
		Delay_ms(20);	//延时消抖
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);	//等待按键松手
		Delay_ms(20);	//延时消抖
		KeyNum = 2;		//置键码为2
	}
	return KeyNum;
}
