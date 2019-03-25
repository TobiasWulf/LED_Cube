/*
 *  Project: EesteCube (5x5x5)
 *  animation.c
 *
 *  Created: 17.12.2011 13:58:32
 *  Author: Tobias Wulf
 *  
 *  GPL lisence
 */
  

 #include "cube.h"
 #include <stdlib.h>
 #include <avr/pgmspace.h>

// 6 frame animation of line spinning around the center of the cube
// the animation is in 2 dimensions.
const unsigned char spinning_line[6][5] PROGMEM =
{
	{ 0x10, 0x08, 0x04, 0x02, 0x01 },
	{ 0x00, 0x18, 0x04, 0x03, 0x00 },
	{ 0x00, 0x03, 0x04, 0x18, 0x00 },
	{ 0x01, 0x02, 0x04, 0x08, 0x10 },
	{ 0x02, 0x02, 0x04, 0x08, 0x08 },
	{ 0x08, 0x08, 0x04, 0x02, 0x02 },
};

// Shows an animation of a spinning spiral
void effect_spiral(int direction, int iterations, int delay)
{
	int i;
	int z;		// cube level

	for (i=0;i<iterations;i++)
	{
		// Loop cube levels
		for (z=0;z<5;z++)
		{
			// Read the animation from program memory and put it in the cube buffer.
			// y=0 and y=2 is stored in the upper nibble of the byte, and must be bitshifted into place.
			cube[z][0] = pgm_read_byte(&spinning_line[(i+z)%6][0]);
			cube[z][1] = pgm_read_byte(&spinning_line[(i+z)%6][1]);
			cube[z][2] = pgm_read_byte(&spinning_line[(i+z)%6][2]);
			cube[z][3] = pgm_read_byte(&spinning_line[(i+z)%6][3]);
			cube[z][4] = pgm_read_byte(&spinning_line[(i+z)%6][4]);
			// the +z makes the animation iterate one step for each plane
			// making it into a spiral
		}
		delay_ms(delay);
	}
}

// Shows an animation of a spinning plane.
void effect_spinning_plane(int direction, int iterations, int delay)
{
	int i;
	int z;		// cube level

	for (i=0;i<iterations;i++)
	{
		// Loop cube levels.
		for (z=0;z<5;z++)
		{
			cube[z][0] = pgm_read_byte(&spinning_line[(i)%6][0]);
			cube[z][1] = pgm_read_byte(&spinning_line[(i)%6][1]);
			cube[z][2] = pgm_read_byte(&spinning_line[(i)%6][2]);
			cube[z][3] = pgm_read_byte(&spinning_line[(i)%6][3]);
			cube[z][4] = pgm_read_byte(&spinning_line[(i)%6][4]);
		}
		delay_ms(delay);
	}
}

//init

void foo(char *a){
}

void effect_everything_bitches(int direction, int iterations, int delay)
{
	int i;

	for(i=0;i<4;i++)	
		effect_rings(1,10,0);
	for(i=0;i<4;i++)	
		effect_explosion(1,10,0);
	for(i=0;i<16;i++)		
		effect_snow(1,10,385);
	for(i=0;i<64;i++)		
		effect_blink(1,10,10);
	for(i=0;i<128;i++)	
		effect_noise(1,10,10);
		
}

void effect_rings(int direction, int iterations, int delay)
{
	char Array[5][5][5];

	int i,j,k,rand;
	for (i=0;i<5;i++)
		for (j=0;j<5;j++)
			for (k=0;k<5;k++)
				{
					Array[i][j][k]=0;
				}
				
	grow2(Array,delay);

}

				
void effect_explosion(int direction, int iterations, int delay)
{
	char Array[5][5][5];

	int i,j,k,rand;
	for (i=0;i<5;i++)
		for (j=0;j<5;j++)
			for (k=0;k<5;k++)
				{
					Array[i][j][k]=0;
				}
				
	grow(Array,delay);

	
	for (i=0;i<5;i++)
		for (j=0;j<5;j++)
			for (k=0;k<5;k++)
				{
				rand=random()%3;
				if(rand==0)
					Array[i][j][k]=1;
				else
					Array[i][j][k]=0;
				}

	
	shrink(Array,delay);
	grow(Array,delay);
	
		
	for (i=0;i<5;i++)
		for (j=0;j<5;j++)
			for (k=0;k<5;k++)
				{
					Array[i][j][k]=0;
				}
				
	shrink(Array,delay);


}

void grow(char Array[5][5][5], int delay)
{
	double a,r=0;
	int i,j,k;

	for(a=0;a<45;a++)
	{
	for (i=0;i<5;i++)
	{
	for (j=0;j<5;j++)
	{
	for (k=0;k<5;k++)
		{
		if(sqrt((i-2)*(i-2)+(j-2)*(j-2)+(k-2)*(k-2))<r)
			setLED(i,j,k);
		else
			if(Array[i][j][k]==1)
				setLED(i,j,k);
			else
				clrLED(i,j,k);
		}
	}
	}
	r=a/10;
	delay_ms(delay);
	}
}

void grow2(char Array[5][5][5], int delay)
{
	double a,r=0;
	int i,j,k;

	for(a=4;a<36;a++)
	{
		for (i=0;i<5;i++)
		{
			for (j=0;j<5;j++)
			{
			for (k=0;k<5;k++)
				{
				if(sqrt((i-2)*(i-2)+(j-2)*(j-2)+(k-2)*(k-2))<r)
					setLED(i,j,k);
				/*else
					if(Array[i][j][k]==1)
						setLED(i,j,k);*/
					else
						clrLED(i,j,k);
				if(sqrt((i-2)*(i-2)+(j-2)*(j-2)+(k-2)*(k-2))<r-0.7)
					clrLED(i,j,k);
				
				}
			}
		}
	r=a/10;
	delay_ms(delay);
	}
}

void shrink(char Array[5][5][5], int delay)
{
	double a,r=0;
	int i,j,k;
	for(a=45;a>=0;a--)
	{
	r=a/10;
	for (i=0;i<5;i++)
	{
	for (j=0;j<5;j++)
	{
	for (k=0;k<5;k++)
		{
		if(sqrt((i-2)*(i-2)+(j-2)*(j-2)+(k-2)*(k-2))<r)
			setLED(i,j,k);
		else
			if(Array[i][j][k]==1)
				setLED(i,j,k);
			else
				clrLED(i,j,k);
		}
	}
	}
	delay_ms(delay);
	}	

}


int bla=0;
int up=1;
void effect_blink(int direction, int iterations, int delay)
{
	dim(bla);
	if(up==1) 
		{
		bla++;
		if(bla==9) up=0;
		}
	if(up==0) 
		{
		bla--;
		if(bla==0) up=1;
		}
}

void dim(int intensity){
for(int i=0;i<10;i++){
	intensity = intensity%10;
	fill(0x1f);
	delay_ms(intensity);
	fill(0x00);
	delay_ms(10-intensity);
	}
}

void effect_snow(int direction, int iterations, int delay)
{
	int i,j,k;
	int a;
	
	for (i=0;i<5;i++)
	{
	for (j=0;j<5;j++)
	{
	for (k=0;k<4;k++)
		{
			if(getLED(i,j,k+1))
				setLED(i,j,k);
			else
				clrLED(i,j,k);
		}
	}
	
	}
		for (i=0;i<5;i++)
		for (j=0;j<5;j++){
				a=random()%8;
				if(a==0)
					setLED(i,j,4);
				else
					clrLED(i,j,4);
				}
	delay_ms(delay);	
}

void effect_noise(int direction, int iterations, int delay)
{
		int i,j,k;
		int a;
	for (i=0;i<5;i++)
	{
	for (j=0;j<5;j++)
	{
	for (k=0;k<5;k++)
		{
		
		a=random()%2;
		if(a)
			setLED(i,j,k);
		else
			clrLED(i,j,k);
		}
	}
	}	
}

void effect_wasdf3(int direction, int iterations, int delay)
{
		int i,j,k;
		int a;
	for (i=0;i<5;i++)
	{
	for (j=0;j<5;j++)
	{
	for (k=0;k<5;k++)
		{
		a=random()%2;
		if(a)
			setLED(i,j,k);
		}
	}
	}
	delay_ms(1000);
	fill(0x00);

	
}

void effect_wasdf2(int direction, int iterations, int delay)
{
	int i,j,k;
	for (i=0;i<5;i++)
	{
	for (j=0;j<5;j++)
	{
	for (k=0;k<5;k++)
		{
		setLED(i,j,k);
		delay_ms(20);
		fill(0x00);
		}
	}
	}
	
	/*fill(0x1f);
	delay_ms(10);
	fill(0x00);
	delay_ms(10);*/

	
}


