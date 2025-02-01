#ifndef __DS1302_H__
#define __DS1302_H__

void DS1302_Init(void);
void DS1302_WriteByte(unsigned char Commond,Data);
unsigned char DS1302_ReadByte(unsigned char Commond);
void DS1302_ReadTime(void);
void DS1302_SetTime(void);

extern char DS1302_Time[];

#endif