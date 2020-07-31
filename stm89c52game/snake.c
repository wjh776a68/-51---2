/*********************************************************************
			̰����Դ��snake.c
**********************************************************************/
#include "config.h"

/******������صĽṹ�嶨��*************/
static struct Food
{
	unsigned char x;	// ʳ��ĺ�����
	unsigned char y;	// ʳ���������
//	unsigned char yes;
}food;	// ʳ��ṹ��

struct Snake
{
	char x[SNAKE_Max_Long];
	char y[SNAKE_Max_Long];
	unsigned char Long;		// �ߵĳ���
	unsigned char Life;		// �ߵ�����
//	unsigned char Score;	// �ߵķ�����������ûʹ��
	unsigned char Level;	// �ߵĵȼ�
	unsigned char Dir;		// ���ƶ�����
}snake;	// �߽ṹ��
/****************************************/

enum Dir{up, down, left, right}; //����ö��


/***********��������***************/
unsigned char DispRAM[8]={0}; // �����껺��
unsigned char tCount,n;
unsigned char keyValue=right;
unsigned char speedLevel=25;
extern uchar keyVal; // ��Դ��key.c

unsigned char code music_tab[] ={   
0x20, 0x18, 0x1C, 0x30, 0x10, 0x40, 0x80, 0x2B //��ʽΪ: ����1������2������3������4���Զ���ײǽ��ײ��    
} ;
/**********************************/

void delay (unsigned char m)   //����Ƶ����ʱ    
{   
 unsigned i=3*m;   
 while(--i);   
}  

// �ô˺���������ʳ�����ʹ�ߵĳ��Ȳ�Ҫ��ô������Խ������Խ���ң��ݹ�Խ��
static void createFood()
{
	unsigned char i;
	food.x = rand()%WIDTH;
	food.y = rand()%LENGTH;
	for(i=0; i<snake.Long; i++)
	{
		if(food.x==snake.x[i] && food.y==snake.y[i])
		createFood();	
	}
}

/****************��ʼ���ߵ�λ�õ�***********************/
static void initSnake()
{
	/********����ڴ�����**********/
	unsigned char i;
	for(i=0; i<SNAKE_Max_Long; i++)
	{
		snake.x[i]=-1;
		snake.y[i]=-1;
	}
	
	/********��ʼ���߲���**********/
	snake.Long=2;	// ��ʼ���ߵĳ���Ϊ����
	snake.Life=1;	//��ʼ���߻���
	snake.Dir=right;
	snake.x[1]=0;
	snake.y[1]=2;
	snake.x[0]=1;
	snake.y[0]=2;
	createFood();
}

/********************ˢ�½���*******************/
static void drawSnake()
{
	unsigned char i=0;
	for(i=0; i<8; i++) DispRAM[i]=0;
	for(i=0; i<snake.Long; i++)
		DispRAM[snake.y[i]] |= 1<<snake.x[i];
	scanDisplay(DispRAM);
	drawPoint(food.x, food.y);
}

/********************���˶�����ˢ��*******************/
static void runSnake()
{

	unsigned char i;
	
	// �����������ƶ�����ͷ��������������β�����ƶ�
	for(i=snake.Long; i>0; i--)
	{	
		snake.y[i]=snake.y[i-1];
		snake.x[i]=snake.x[i-1];
	}
	
	// ���»���ߵ�ͷ��λ��
	switch(snake.Dir)
	{	
		case up:	snake.y[0]-=1; break;
		case down:	snake.y[0]+=1; break;
		case left:	snake.x[0]-=1; break;
		case right: snake.x[0]+=1; break;
		default: break;
	}
	
	// �߳Ե�ʳ��
	if(snake.x[0]==food.x && snake.y[0]==food.y)
	{  	
   		
		n=200;
		while(n--)    Beep=~Beep,delay(music_tab[4]); 


		snake.Long++;
		createFood();
	}
	

}

/*******************���򰴼�����***********************/
static void changeDir(unsigned char key)
{
	// ���򰴼��Ĺ���
	switch(key)
	{
		case up:	if(snake.Dir != down)	snake.Dir=up; 		break;
		case down: 	if(snake.Dir != up)		snake.Dir=down; 	break;
		case left: 	if(snake.Dir != right) 	snake.Dir=left; 	break;
		case right: if(snake.Dir != left) 	snake.Dir=right;	break;
		default: break;
	}
}

/********************����̰������Ϸ����������*********************/
void startSnake()
{
	
	uchar i=0;
	initSnake();
	n=200;
	while(n--)    Beep=~Beep,delay(music_tab[5]); 
	while(snake.Life)
	{
		changeDir(keyValue);
		
		// �����е��ٶȣ���speedLevel����
		if(tCount >= speedLevel)
		{
			tCount=0;
			runSnake();
		}
			
		/**********************��֮dead***************************/
		// �޶��߻��Χ������Χ��dead
		if((snake.x[0]>(WIDTH-1)) || (snake.x[0]<0) || (snake.y[0]>(LENGTH-1)) || (snake.y[0]<0))
		{
			
			snake.Life=0;	
			snake.Level=1;
			speedLevel=25;
			keyVal=right;	
		}
		// ����ɱ���
		for(i=4; i<=snake.Long; i++)
		{
			
			if(snake.x[i-1]==snake.x[0] && snake.y[i-1]==snake.y[0])
			{  	
				n=200;
			 	while(n--)    Beep=~Beep,delay(music_tab[6]); 
				snake.Life=0;
				snake.Level=1;
				speedLevel=25;
				keyVal=right;	
			}
		}
		/***********************************************************/
		
		// �ȼ�Խ���ٶ�Խ��
		if(snake.Long >= SNAKE_Max_Long)
		{
			delayMs(500); // ��һ��ʱ
			initSnake();
			speedLevel-=5;
			keyVal=right;			
			if(++snake.Level > 5)
			{
				// �������Ѿ��򱬻��ˣ����ڴ�ͷ����������
				n=200;
			 	while(n--)    Beep=~Beep,delay(music_tab[7]);
				snake.Level=1;
				speedLevel=25;						
			}
			tCount=0;
		}
		drawSnake();
	}
}
