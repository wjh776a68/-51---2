#include "config.h"
/**************************************************************************
******	����������ʱ�����������STC-ISP�л�ã���12MHz����Ϊʱ��Դ
******	STC-ISP������ص�ַ��WWW.STCMCU.COM
**************************************************************************/

//void delayUs(unsigned int i)
//{
//	while(i--)
//		_nop_();
//}

void delay1Ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void delayMs(unsigned int i)
{
	while(i--)
	{
		delay1Ms();
	}
}
