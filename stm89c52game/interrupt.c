#include "config.h"

extern unsigned char tCount;	//��Դ��snake.c�ļ�
extern unsigned char keyValue;	//��Դ��snake.c�ļ�
	   

//******��ʱ��0��ʼ��*************//
void initTimer0()
{
	TMOD |= 0x01;
	TL0 = TIMER;
	TH0 = TIMER>>8;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

//******��ʱ��0�жϷ�����*************//



void timer0Handle() interrupt 1
{	// 20ms�ж�



	TL0 = TIMER;
	TH0 = TIMER>>8;
	keyValue=scanKey();
	tCount++;
	
}