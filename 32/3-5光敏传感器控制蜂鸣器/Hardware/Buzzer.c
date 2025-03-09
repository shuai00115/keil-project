#include "stm32f10x.h"                  // Device header

/*
**函数：Buzzer初始化
**参数：无
**返回值：无
*/

void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //开启GPIOA的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);									//设置PA12引脚为推挽输出
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);		//设置PA12引脚初始为高电平
	
	
}
/*
**函数：Buzzer开启
**参数：无
**返回值：无
*/

void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}

/*
**函数：Buzzer关闭
**参数：无
**返回值：无
*/

void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

/*
**函数：Buzzer反转
**参数：无
**返回值：无
*/

void Buzzer_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12) == 0)	//获取输出寄存器的状态，如果当前引脚为低电平
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	}
	else	//否则即当前引脚为高电平
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
}
