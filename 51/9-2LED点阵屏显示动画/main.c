#include <REGX52.H>
#include "Delay.h"
#include "MATRIXLED.h"

unsigned char code Animation[]={
0x00,0x00,0x1F,0x3C,0x1F,0x00,0x00,0x00, 
0x00,0x00,0x07,0x1C,0x3F,0x60,0x00,0x00,
};

void main()
{
	unsigned char i,Offset,Count=0;
	Matrix_Init();
	while(1)
	{
		for(i=0;i<8;i++)
		{
			MatrixLED_ShowColumn(i,Animation[i+Offset]);
		}
		Count++;
		if(Count>30)
		{
			Count=0;
			Offset+=8;
			if(Offset>8)
			{
				Offset=0;
			}
		}
	}
}