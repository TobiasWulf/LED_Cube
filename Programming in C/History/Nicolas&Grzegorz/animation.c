/*
 *  Project: EesteCube (5x5x5)
 *  animation.c
 *
 *  Created: 17.12.2011 13:58:32
 *  Author: Tobias Wulf
 *  
 *  GPL lisence
 */
  
 #include <stdio.h>


 #include "cube.h"
 #include <stdlib.h>
 #include <avr/pgmspace.h>
 //#include <time.h> 
 
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


// animate E

void animateE ()
{
	for(int z = 0;z<5;z++)
	{
		
			fill(0x00);
			cube[0][z] = 0x1F;
			cube[1][z] = 0x01;
			cube[2][z] = 0x07;
			cube[3][z] = 0x01;
			cube[4][z] = 0x1F;
			//for(int y = 1; y < 5; y++)
			//{
			//	for(int z = 0; z < 5 ; z++)
			//	{
			//		cube[z][y] = cube[z][y-1];
			//	}
			//}
		
		delay_ms(500); 
	}
}

void eestecAnimation ()
{
int letter=0,l=0;
	while(1)
	{
		if(l==5)
		{
			l=0;
		}
		if(letter == 6)
		{
			letter = 0;
		}
		
		switch(letter)
		{
		case 0:
			writeE(l);
			break;
			
		case 1:
			writeE(l);
			break;
			
		case 2:
			writeS(l);
			break;
			
		case 3:
			writeT(l);
			break;
			
		case 4:
			writeE(l);
			break;
			
		case 5:
			writeC(l);
			break;
		}
		
		letter++;
		l++;
		delay_ms(500); 
	}
}


void alphabet()
{
	int letter=0, l = 4;
	for(letter=0;letter<24;letter++)
	{
		getLetter(letter,l);
		delay_ms(700); 
	}

}

void animateLetter(int letter)
{
	int l=0;
	for(l=0;l<4;l++)
	{
		getLetter(letter,l);
		delay_ms(80);
	}
		getLetter(letter,l);
		delay_ms(500);

	
	
}

void animateCharacter(char charletter)
{
	int letter = letterToInt(charletter);
	int l=0;
	for(l=0;l<4;l++)
	{
		getLetter(letter,l);
		delay_ms(80);
	}
		getLetter(letter,l);
		delay_ms(500);

	
	
}

void writeBlank()
{
		fill(0x00);
		delay_ms(900);

}


void writeEestec()
{
	animateCharacter('E');
	animateCharacter('E');
	animateCharacter('S');
	animateCharacter('T');
	animateCharacter('E');
	animateCharacter('C');
}

void writeFilRos()
{
	animateCharacter('F');
	animateCharacter('I');
	animateCharacter('L');
	animateCharacter('R');
	animateCharacter('O');
	animateCharacter('S');
	writeBlank();
	animateCharacter('R');
	animateCharacter('U');
	animateCharacter('L');
	animateCharacter('Z');


}

void LCKrakow()
{
	animateCharacter('E');
	animateCharacter('E');
	animateCharacter('S');
	animateCharacter('T');
	animateCharacter('E');
	animateCharacter('C');
	writeBlank();
	animateCharacter('L');
	animateCharacter('C');
	writeBlank();
	animateCharacter('K');
	animateCharacter('R');
	animateCharacter('A');
	animateCharacter('K');
	animateCharacter('O');
	animateCharacter('W');
}


void matrix()
{
		fill(0x00);
		while(1)
	{

		generateDot();

		delay_ms(90);
		moveDot();
		
	}
/*		generateDot();

		delay_ms(9000);
	}*/
}

void generateDot()
{
	//unsigned int iseed = (unsigned int)time(NULL);
	//srand (iseed);
	int x = rand() % 5;
	int y = rand() % 5;
	int z = 4;
	setLED(x,y,z);
}

void moveDot()
{
	for(int x=0;x<5;x++)
	{
		for(int y=0;y<5;y++)
		{
		for(int z=0;z<5;z++)
			{	
				if(getLED(x,y,z) != 0x00)
				{
					if(z==0)
					{
						clrLED(x,y,z);
					}
					else
					{
						clrLED(x,y,z);
						setLED(x,y,z-1);
					}
					
				}
				
			}
		}
		
	}
}