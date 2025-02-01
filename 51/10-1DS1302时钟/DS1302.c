#include <REGX52.H>


//定义引脚
sbit DS1302_SLCK=P3^6;
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;


#define DS1302_Second   0x80
#define DS1302_Minute   0x82
#define DS1302_Hour     0x84
#define DS1302_Date     0x86
#define DS1302_Month    0x88
#define DS1302_Day      0x8A
#define DS1302_Year     0x8C
#define DS1302_WP       0x8E

//定义的时间数据，从索引0~6分别为年，月，日，小时，分钟，秒，星期。
unsigned char DS1302_Time[]={24,11,18,21,13,50,1};

/**
  * @brief DS1302初始化
  * @param  无
  * @retval 无
  */

void DS1302_Init(void)
{
	DS1302_CE=0;
	DS1302_SLCK=0;
}

/**
  * @brief 将数据写入DS1302
  * @param  写入的寄存器地址Commond及数据Data
  * @retval 无
  */

void DS1302_WriteByte(unsigned char Commond,Data)
{
	unsigned char i;
	DS1302_CE=1;
	
	for(i=0;i<8;i++)
	{
		DS1302_IO=Commond&(0x01<<i);
		DS1302_SLCK=1;
		DS1302_SLCK=0;	
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO=Data&(0x01<<i);
		DS1302_SLCK=1;
		DS1302_SLCK=0;	
	}

		DS1302_CE=0;
}

/**
  * @brief 从DS1302寄存器中读取数据
  * @param  需要读取的寄存器的地址Commond
  * @retval 寄存器中的数据
  */

unsigned char DS1302_ReadByte(unsigned char Commond)
{
	unsigned char i,Data=0x00;
	Commond|=0x01;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Commond&(0x01<<i);
		DS1302_SLCK=0;
		DS1302_SLCK=1;	
	}
	for(i=0;i<8;i++)
	{
		DS1302_SLCK=1;
		DS1302_SLCK=0;
		if(DS1302_IO) {Data|=(0x01<<i);}
	}
	DS1302_CE=0;
	DS1302_IO=0;
	return Data;

}

/**
  * @brief 设定DS1302定时器的时钟数据
  * @param  无
  * @retval 无
  */

void DS1302_SetTime(void)
{
	DS1302_WriteByte(DS1302_WP,0x00);
	DS1302_WriteByte(DS1302_Year,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_Month,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_Date,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_Hour,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_Minute,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_Second,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_Day,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);
}

/**
  * @brief 从DS1302中读取时间数据
  * @param  无
  * @retval 无
  */

void DS1302_ReadTime(void)
{
	unsigned char Temp;
	Temp=DS1302_ReadByte(DS1302_Year);
	DS1302_Time[0]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_Month);
	DS1302_Time[1]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_Date);
	DS1302_Time[2]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_Hour);
	DS1302_Time[3]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_Minute);
	DS1302_Time[4]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_Second);
	DS1302_Time[5]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_Day);
	DS1302_Time[6]=Temp/16*10+Temp%16;
	
}