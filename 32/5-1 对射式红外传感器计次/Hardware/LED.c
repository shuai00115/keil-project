#include "stm32f10x.h"                  // Device header

/*
**函数：LED初始化
**参数：无
**返回值：无
*/

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //开启GPIOA的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);									//设置PA1和PA2引脚为推挽输出
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);		//设置PA1和PA2引脚初始为高电平
	
	
}

/*
**函数：LED1开启
**参数：无
**返回值：无
*/

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}

/*
**函数：LED1关闭
**参数：无
**返回值：无
*/

void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

/*
**函数：LED1反转
**参数：无
**返回值：无
*/

void LED1_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == 0)	//获取输出寄存器的状态，如果当前引脚为低电平
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else	//否则即当前引脚为高电平
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
}

/*
**函数：LED2开启
**参数：无
**返回值：无
*/

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

/*
**函数：LED2关闭
**参数：无
**返回值：无
*/

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

/*
**函数：LED2反转
**参数：无
**返回值：无
*/

void LED2_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2) == 0)	//获取输出寄存器的状态，如果当前引脚为低电平
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else	//否则即当前引脚为高电平
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
}

