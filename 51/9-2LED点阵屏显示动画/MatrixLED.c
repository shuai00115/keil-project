#include <REGX52.H>
#include "Delay.h"


sbit RCK = P3^5;			//RCLK
sbit SCK = P3^6;			//SRCLK
sbit SER = P3^4;			//SER

#define MATRIX_LED_PORT P0

/**
  * @brief 74H595写入一个字节
  * @param  要写入的字节
  * @retval 无
  */

void _74H959_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER=Byte&(0x80>>i);
		SCK=1;
		SCK=0;
	}
	RCK=1;	
	RCK=0;
}

/**
  * @brief 点阵屏初始化
  * @param  无
  * @retval 无
  */

void Matrix_Init()
{
	SCK=0;
	RCK=0;
}

/**
  * @brief LED点阵屏显示一列数据
	* @param  Column要选择的列，范围0~7,0为最左边
	* @param Data选择显示的数据，高位在上，1为亮，0为灭
  * @retval 无
  */

void MatrixLED_ShowColumn(unsigned char Column,Data)
{
	_74H959_WriteByte(Data);
	MATRIX_LED_PORT=~(0x80>>Column);
	Delay(1);
	MATRIX_LED_PORT=0xFF;
}

