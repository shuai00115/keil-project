#include <REGX52.H>
#include "Delay.h"
#include "Nixie.h"

void main()
{
	while(1)
	{
		Nixie(1,6);
		Nixie(2,6);
		Nixie(3,6);
		Nixie(4,6);
		Nixie(5,6);
		Nixie(6,6);
		Nixie(7,6);
		Nixie(8,6);
	}
}