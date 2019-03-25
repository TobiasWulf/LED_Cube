#define Time 500
#include "cube.h"
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <stdio.h>

//#include <time.h>


volatile int position[3];
volatile int head[3];
int *posx;
int *posy;
int *posz;

int fruit[3];
int *fruitx;
int *fruity;
int *fruitz;

volatile int snake[30][3];

void fillSnake()
{
	for(int a=0;a<30;a++)
	{
		for(int b=0;b<3;b++)
		{
		 snake[a][b]=-1;
		}
	}
}

void displaySnake()
{
int a,b;
//while(snake[a][b]!=-1)
	for( a=0;a<30;a++)
	{
		for( b=0;b<3;b++)
		{
		if(snake[a][b]==-1)
		 break;
		setLED(snake[a][0],snake[a][1],snake[a][2]);

		}
		if(snake[a][b]==-1)
		 break;
	}
}

void snakeMove()
{
	int a,b;
	int tmp[3];
	if(snake[1][0]!=-1)
	{
		for(b=0;b<3;b++)
		{
			tmp[b] = snake[1][b];
			snake[1][b] = snake[2][b];
		}
		for(a=2;a<30;a++)
		{
			for(b=0;b<3;b++)
			{
				if(snake[a+1][b]==-1)
					break;
				snake[a][b]=tmp[b];
				tmp[b] = snake[a+1][b];
				snake[a+1][b] = snake[a][b];
			}
			if(snake[a+1][b]==-1)
			break;
		}
		
			switch(direction)
		{
			case 0: // x+
				
				snake[a+1][0]=snake[a+1][0]++;
				break;
				

			case 1: // y+
				snake[a+1][1]=snake[a+1][1]++;
				break;

			
			case 2: // z+
				snake[a+1][2]=snake[a+1][2]++;
				break;

		}

		if(snake[a+1][0]>4) snake[a][0] = 0;
		if(snake[a+1][1]>4) snake[a][1] = 0;
		if(snake[a+1][2]>4) snake[a][2] = 0;
		if(snake[a+1][0]<0) snake[a][0] = 4;
		if(snake[a+1][1]<0) snake[a][1] = 4;
		if(snake[a+1][2]<0) snake[a][2] = 4;
		
		head[0] = snake[a+1][0];
		head[1] = snake[a+1][1];
		head[2] = snake[a+1][2];
	}
	else
	{
		switch(direction)
		{
			case 0: // x+
				
				snake[a][0]=snake[a][0]+1;
				if(snake[a][0]>4) snake[a][0] = 0;
				if(snake[a][1]>4) snake[a][1] = 0;
				if(snake[a][2]>4) snake[a][2] = 0;
				if(snake[a][0]<0) snake[a][0] = 4;
				if(snake[a][1]<0) snake[a][1] = 4;
				if(snake[a][2]<0) snake[a][2] = 4;
				break;
				
			case 3: // x-
				snake[a][0]=snake[a][0]--;
				if(snake[a][0]>4) snake[a][0] = 0;
				if(snake[a][1]>4) snake[a][1] = 0;
				if(snake[a][2]>4) snake[a][2] = 0;
				if(snake[a][0]<0) snake[a][0] = 4;
				if(snake[a][1]<0) snake[a][1] = 4;
				if(snake[a][2]<0) snake[a][2] = 4;
				break;
			
			case 1: // y+
				snake[a][1]=snake[a][1]++;
				if(snake[a][0]>4) snake[a][0] = 0;
				if(snake[a][1]>4) snake[a][1] = 0;
				if(snake[a][2]>4) snake[a][2] = 0;
				if(snake[a][0]<0) snake[a][0] = 4;
				if(snake[a][1]<0) snake[a][1] = 4;
				if(snake[a][2]<0) snake[a][2] = 4;
				break;
				
			case 4: // y-
				snake[a][1]=snake[a][1]--;
				if(snake[a][0]>4) snake[a][0] = 0;
				if(snake[a][1]>4) snake[a][1] = 0;
				if(snake[a][2]>4) snake[a][2] = 0;
				if(snake[a][0]<0) snake[a][0] = 4;
				if(snake[a][1]<0) snake[a][1] = 4;
				if(snake[a][2]<0) snake[a][2] = 4;
				break;
			
			case 2: // z+
				snake[a][2]=snake[a][2]++;
				if(snake[a][0]>4) snake[a][0] = 0;
				if(snake[a][1]>4) snake[a][1] = 0;
				if(snake[a][2]>4) snake[a][2] = 0;
				if(snake[a][0]<0) snake[a][0] = 4;
				if(snake[a][1]<0) snake[a][1] = 4;
				if(snake[a][2]<0) snake[a][2] = 4;
				break;
				
			case 5: // z-
				snake[a][2]=snake[a][2]--;				
				if(snake[a][0]>4) snake[a][0] = 0;
				if(snake[a][1]>4) snake[a][1] = 0;
				if(snake[a][2]>4) snake[a][2] = 0;
				if(snake[a][0]<0) snake[a][0] = 4;
				if(snake[a][1]<0) snake[a][1] = 4;
				if(snake[a][2]<0) snake[a][2] = 4;
				break;
			
		}
		head[0] = snake[a][0];
		head[1] = snake[a][1];
		head[2] = snake[a][2];
	}
}
void directionHandler()
{
	snakeMove();	

	
}

void fruitHandler(int* pos, int* fruit)
{
	
	
	if((head[0] == fruit[0]) && (head[1] == fruit[1]) && (head[2] == fruit[2]))
	{
		generateFruitPlace();
		enlarge(head);
	}
}

void enlarge(int* position)
{
	int a;
	for(a=0;a<30;a++)
	{
		if(snake[a][0]==-1)
			break;
	}
	snake[a][0] = position[0];
	snake[a][1] = position[1];
	snake[a][2] = position[2];
	
}

void generateFruitPlace()
{
	int x,y,z;
	do{
	x = rand()%5;
	y = rand()%5;
	z = rand()%5;
	}
	while(getLED(x,y,z)==0x01);
	
	fruit[0] = x;
	fruit[1] = y;
	fruit[2] = z;
	setLED(fruit[0],fruit[1],fruit[2]);
}

void check()
{
	switch(direction)
	{
		case 0:
			setLED(0,0,0);
			break;
			case 1:
			setLED(0,4,0);
			break;
			case 2:
			setLED(0,0,4);
			break;
	}
	delay_ms(50);
}


void start()
{
	position[0]=0;
	position[1]=0;
	position[2]=0;
	fillSnake();
	snake[0][0] = position[0];
	snake[0][1] = position[1];
	snake[0][2] = position[2];
	
	 *posx = position[0];
	 *posy = position[1];
	 *posz = position[2];
	 *fruitx = fruit[0];
	 *fruity = fruit[1];
	 *fruitz = fruit[2];
	int x=0,y=0,z=0;
	//unsigned int iseed = (unsigned int)time(NULL);
	//srand (iseed);
	generateFruitPlace();
	
	while(1)
	{

		fill(0x00);
		//
		//setLED(position[0],position[1],position[2]);
		//displaySnake();
		check();
		//setLED(fruit[0],fruit[1],fruit[2]);
		//directionHandler();
		//fruitHandler(position,fruit);
		
		delay_ms(Time);
		
	}
}
