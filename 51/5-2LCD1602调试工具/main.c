
#include "lcd1602.h"
#include "public.h"

void main()
{	
	lcd1602_init();//LCD1602???
	lcd1602_show_string(0,0,"xiaoshuai");//?????
	lcd1602_show_string(0,1,"666");
	while(1)
	{
		
	}	
}