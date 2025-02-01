#include <REGX52.H>
#include <INTRINS.H>


void Delay(xms)		//@11.0592MHz
{
	unsigned char i, j;
	while(xms--)
	{
		_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
	}
	
}


void Nixie(unsigned char location)
{
	switch(location)
	{
		case 1:P2_4 = 0;P2_3 = 0;P2_2 = 0;break;
		case 2:P2_4 = 0;P2_3 = 0;P2_2 = 1;break;
		case 3:P2_4 = 0;P2_3 = 1;P2_2 = 0;break;
		case 4:P2_4 = 0;P2_3 = 1;P2_2 = 1;break;
		case 5:P2_4 = 1;P2_3 = 0;P2_2 = 0;break;
		case 6:P2_4 = 1;P2_3 = 0;P2_2 = 1;break;
		case 7:P2_4 = 1;P2_3 = 1;P2_2 = 0;break;
		case 8:P2_4 = 1;P2_3 = 1;P2_2 = 1;break;		
	}
	
	

}


void main()
{
	
	while(1)
	{
		Nixie(8);
		P0 = 0x6D;
		Delay(1);
		P0 = 0x00;
		Nixie(7);
		P0 = 0x7F;
		Delay(1);
		P0 = 0x00;
	}
}
 