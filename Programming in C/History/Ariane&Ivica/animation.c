/*
 *  Project: EesteCube (5x5x5)
 *  animation.c
 *
 *  Created: 17.12.2011 13:58:32
 *  Author: Tobias Wulf & Ariane Raschke
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


void shiftBack()
{
int i,j,k;
       for (i=4;i>0;i--)
       {
       for (j=0;j<5;j++)
       {
       for (k=0;k<5;k++)
               {
                       if(getLED(i-1,j,k)){
                               setLED(i,j,k);
							   //clrLED(i-1,j,k);
							   }
                       else
                               clrLED(i,j,k);
               }
       }
}
}

void shiftBack2()
{
int i,j,k;
    for (i=4;i>0;i--)
    {
        for (j=0;j<1;j++)
        {
			for (k=0;k<5;k++)
            {
                if(getLED(i-1,j,k))
                    setLED(i,j,k);
							   //clrLED(i-1,j,k);
                else
                    clrLED(i,j,k);
			}
        }
	}

}

void shiftLeft()
{
int i,j,k;



       for (j=0;j<4;j++)
       {
       for (k=0;k<5;k++)
       {
                       if(getLED(0,j+1,k)){
                            setLED(0,j,k);
							//clrLED(0,j+1,k);
							  }
                       else
                               clrLED(0,j,k);
        }


}
/*for(i=4;i>0;i--)
{
	for (j = 0; j < 5; j++)
		{	
		if(getLED(i-1,0,j)){
			setLED(i,0,j);
			clrLED(i-1,0,j);
		}
		else
			clrLED(i,0,j);
		}
	
}*/
shiftBack2();


delay_ms(150);
}


void effect_EESTEC()
{
	fill(0);	// E
	delay_ms(70);
	line_z(0, 0, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	delay_ms(250);
	
	
	fill(0);	// E  
	delay_ms(70);
	line_z(0, 0, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	delay_ms(250);
	
	fill(0);     // S
	delay_ms(70);
	setLED(0, 0, 3);	
	setLED(0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	clrLED(0,4,0);
	clrLED(0,0,4);
	delay_ms(250);
	
	fill(0);	// T
	delay_ms(70);
	line_y(4, 0, 0, 4, 1);
	line_z(0, 2, 0, 4, 1);
	delay_ms(250);
		
	fill(0);	// E
	delay_ms(70);
	line_z(0, 0, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	delay_ms(250);
	
	fill(0);	// C
	delay_ms(70);
	line_z(0, 0, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	delay_ms(250);
	
	fill(0);	// W
	delay_ms(270);
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);
	setLED(0, 1, 1);
	setLED(0, 2, 2);
	setLED(0, 3, 1);
	delay_ms(250); 
	
	fill(0);	// H
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);	
	delay_ms(250);
	
	fill(0);	// A
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);	
	line_y(4, 0, 0, 4, 1);	
	clrLED(0, 0, 4);
	clrLED(0, 4, 4);
	delay_ms(250);
	fill(0);
	
	fill(0);	// T
	delay_ms(70);
	line_y(4, 0, 0, 4, 1);
	line_z(0, 2, 0, 4, 1);
	delay_ms(250);
	
	fill(0);	// I
	delay_ms(270);
	line_z(0, 2, 0, 4, 1);
	setLED(0,1,0);
	setLED(0,3,0);	
	setLED(0,1,4);
	setLED(0,3,4);	
	delay_ms(250);
	
	fill(0);     // S
	delay_ms(70);
	setLED(0, 0, 3);	
	setLED(0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	clrLED(0,4,0);
	clrLED(0,0,4);
	delay_ms(250);
	
	fill(0);     // Y
	delay_ms(270);
	line_z(0, 2, 0, 2, 1);
	setLED(0, 1, 3);	
	setLED(0, 3, 3);
	setLED(0, 0, 4);	
	setLED(0, 4, 4);
	delay_ms(250); 
	
	fill(0);	// O
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	clrLED(0, 0, 0);
	clrLED(0, 0, 4);
	clrLED(0, 4, 0);
	clrLED(0, 4, 4);
	delay_ms(250); 
	
	fill(0);	// U
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	clrLED(0, 0, 0);
	clrLED(0, 4, 0);
	delay_ms(250); 
	
	fill(0);	// R
	delay_ms(70);
	line_z(0, 0, 0, 4, 1);		
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	clrLED(0, 4, 2);
	clrLED(0, 4, 4);
	setLED(0, 4, 0);
	setLED(0, 3, 1);
	setLED(0, 4, 3);
	delay_ms(250); 
	
	fill(0);	// P
	delay_ms(270);
	line_z(0, 0, 0, 4, 1);		
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	clrLED(0, 4, 2);
	clrLED(0, 4, 4);
	setLED(0, 4, 3);
	delay_ms(250); 
	
	fill(0);	// R
	delay_ms(70);
	line_z(0, 0, 0, 4, 1);		
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	clrLED(0, 4, 2);
	clrLED(0, 4, 4);
	setLED(0, 4, 0);
	setLED(0, 3, 1);
	setLED(0, 4, 3);
	delay_ms(250); 
	
	fill(0);	// O
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	clrLED(0, 0, 0);
	clrLED(0, 0, 4);
	clrLED(0, 4, 0);
	clrLED(0, 4, 4);
	delay_ms(250);
	
	fill(0);	// F
	delay_ms(70);
	line_z(0, 0, 0, 4, 1);	
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	delay_ms(250);
	
	fill(0);	// E
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	delay_ms(250);
	
		fill(0);     // S
	delay_ms(70);
	setLED(0, 0, 3);	
	setLED(0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	clrLED(0,4,0);
	clrLED(0,0,4);
	delay_ms(250);	
	
	fill(0);     // S
	delay_ms(70);
	setLED(0, 0, 3);	
	setLED(0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	clrLED(0,4,0);
	clrLED(0,0,4);
	delay_ms(250);
	
	fill(0);	// I
	delay_ms(70);
	line_z(0, 2, 0, 4, 1);
	setLED(0,1,0);
	setLED(0,3,0);	
	setLED(0,1,4);
	setLED(0,3,4);	
	delay_ms(250);
	
	fill(0);	// O
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	line_y(4, 0, 0, 4, 1);
	clrLED(0, 0, 0);
	clrLED(0, 0, 4);
	clrLED(0, 4, 0);
	clrLED(0, 4, 4);
	delay_ms(250); 
	
	fill(0);	// N
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);
	setLED(0, 1, 3);
	setLED(0, 2, 2);
	setLED(0, 3, 1);
	delay_ms(250); 
	
	fill(0);	// ?
	delay_ms(70);  
	line_y(4, 0, 1, 3, 1);	
	setLED(0, 0, 3);
	setLED(0, 3, 2);
	setLED(0, 2, 2);
	setLED(0, 2, 0);
	setLED(0, 4, 3);
	delay_ms(650);
	
	fill(0);	// A
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);	
	line_y(4, 0, 0, 4, 1);	
	clrLED(0, 0, 4);
	clrLED(0, 4, 4);
	delay_ms(250);
	fill(0);
	
	fill(0);	// U
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	clrLED(0, 0, 0);
	clrLED(0, 4, 0);
	delay_ms(250);
	
	fill(0);	// !!!
	delay_ms(70);
	line_z(0, 2, 0, 4, 1);
	
	
	line_z(0, 0, 0, 4, 1);
	clrLED(0, 2, 1);
	clrLED(0, 0, 1);
	line_z(0, 4, 0, 4, 1);
	clrLED(0, 4, 1);	
	
	fill(0);	// A
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);	
	line_y(4, 0, 0, 4, 1);	
	clrLED(0, 0, 4);
	clrLED(0, 4, 4);
	delay_ms(250);
	fill(0);
	
	fill(0);	// U
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	clrLED(0, 0, 0);
	clrLED(0, 4, 0);
	delay_ms(250);
	
	fill(0);	// !!!
	delay_ms(70);
	line_z(0, 2, 0, 4, 1);
	
	
	line_z(0, 0, 0, 4, 1);
	clrLED(0, 2, 1);
	clrLED(0, 0, 1);
	line_z(0, 4, 0, 4, 1);
	clrLED(0, 4, 1);	
	
	fill(0);	// A
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);
	line_y(2, 0, 0, 4, 1);	
	line_y(4, 0, 0, 4, 1);	
	clrLED(0, 0, 4);
	clrLED(0, 4, 4);
	delay_ms(250);
	fill(0);
	
	fill(0);	// U
	delay_ms(70);  
	line_z(0, 0, 0, 4, 1);	
	line_z(0, 4, 0, 4, 1);	
	line_y(0, 0, 0, 4, 1);
	clrLED(0, 0, 0);
	clrLED(0, 4, 0);
	delay_ms(250);
	
	fill(0);	// !!!
	delay_ms(70);
	line_z(0, 2, 0, 4, 1);
	
	
	line_z(0, 0, 0, 4, 1);
	clrLED(0, 2, 1);
	clrLED(0, 0, 1);
	line_z(0, 4, 0, 4, 1);
	clrLED(0, 4, 1);	
	
	delay_ms(650);
	fill(0);
	delay_ms(650);
	
	
}


void setLine(int one, int two, int three, int four, int five)
{
	if (one == 0)
	clrLED(0,4,4);
	else setLED(0,4,4);
	if (two == 0) 
	clrLED(0,4,3);
	else setLED(0,4,3);
	if (three == 0) 
	clrLED(0,4,2);
	else setLED(0,4,2);
	if (four == 0) 
	clrLED(0,4,1);
	else setLED(0,4,1);
	if (five == 0) 
	clrLED(0,4,0);
	else setLED(0,4,0);
	shiftLeft();

}

void writeA()
{
 setLine(0,1,1,1,1);
 setLine(1,0,1,0,0);
 setLine(1,0,1,0,0);
 setLine(0,1,1,1,1);
 setLine(0,0,0,0,0);
}

void writeB()
{
setLine(1,1,1,1,1);
setLine(1,0,1,0,1);
setLine(1,0,1,0,1);
setLine(0,1,0,1,0);
setLine(0,0,0,0,0);

}

void writeC()
{
setLine(0,1,1,1,0);
setLine(1,0,0,0,1);
setLine(1,0,0,0,1);
setLine(1,0,0,0,1);
setLine(0,0,0,0,0);

}

void writeD()
{
setLine(1,1,1,1,1);
setLine(1,0,0,0,1);
setLine(1,0,0,0,1);
setLine(0,1,1,1,0);
setLine(0,0,0,0,0);

}

void writeE()
{
setLine(1,1,1,1,1);
setLine(1,0,1,0,1);
setLine(1,0,1,0,1);
setLine(1,0,0,0,1);
setLine(0,0,0,0,0);

}

void writeF()
{
setLine(1,1,1,1,1);
setLine(1,0,1,0,0);
setLine(1,0,1,0,0);
setLine(1,0,0,0,0);
setLine(0,0,0,0,0);

}

void writeG()
{
setLine(0,1,1,1,0);
setLine(1,0,0,0,1);
setLine(1,0,0,0,1);
setLine(1,0,1,0,1);
setLine(1,0,1,1,0);
setLine(0,0,0,0,0);

}

void writeH()
{
setLine(1,1,1,1,1);
setLine(0,0,1,0,0);
setLine(0,0,1,0,0);
setLine(1,1,1,1,1);
setLine(0,0,0,0,0);

}

void writeI()
{
setLine(1,0,0,0,1);
setLine(1,1,1,1,1);
setLine(1,0,0,0,1);
}

void writeJ()
{
setLine(1,0,0,1,0);
setLine(1,0,0,0,1);
setLine(1,0,0,0,1);
setLine(1,1,1,1,0);
setLine(0,0,0,0,0);

}

void writeK()
{
setLine(1,1,1,1,1);
setLine(0,0,1,0,0);
setLine(0,1,0,1,0);
setLine(1,0,0,0,1);
setLine(0,0,0,0,0);

}

void writeL()
{
setLine(1,1,1,1,1);
setLine(0,0,0,0,1);
setLine(0,0,0,0,1);
setLine(0,0,0,0,1);
setLine(0,0,0,0,0);
}

void writeM()
{
setLine(1,1,1,1,1);
setLine(0,1,0,0,0);
setLine(0,0,1,0,0);
setLine(0,1,0,0,0);
setLine(1,1,1,1,1);
setLine(0,0,0,0,0);
}


void writeN()
{
setLine(1,1,1,1,1);
setLine(0,1,0,0,0);
setLine(0,0,1,0,0);
setLine(0,0,0,1,0);
setLine(1,1,1,1,1);
setLine(0,0,0,0,0);
}

void writeO()
{
setLine(0,1,1,1,0);
setLine(1,0,0,0,1);
setLine(1,0,0,0,1);
setLine(0,1,1,1,0);
setLine(0,0,0,0,0);
}

void writeP()
{

setLine(1,1,1,1,1);
setLine(1,0,1,0,0);
setLine(1,0,1,0,0);
setLine(0,1,0,0,0);
setLine(0,0,0,0,0);
}

void writeQ()
{
setLine(0,1,1,1,0);
setLine(1,0,0,0,1);
setLine(1,0,0,1,1);
setLine(0,1,1,1,0);
setLine(0,0,0,0,0);
}


void writeR()
{
setLine(1,1,1,1,1);
setLine(1,0,1,0,0);
setLine(1,0,1,1,0);
setLine(0,1,0,0,1);
setLine(0,0,0,0,0);
}

void writeS()
{
setLine(0,1,0,0,1);
setLine(1,0,1,0,1);
setLine(1,0,1,0,1);
setLine(1,0,0,1,0);
setLine(0,0,0,0,0);

}

void writeT()
{
setLine(1,0,0,0,0);
setLine(1,0,0,0,0);
setLine(1,1,1,1,1);
setLine(1,0,0,0,0);
setLine(1,0,0,0,0);
setLine(0,0,0,0,0);

}


void writeU()
{
setLine(1,1,1,1,0);
setLine(0,0,0,0,1);
setLine(0,0,0,0,1);
setLine(1,1,1,1,0);
setLine(0,0,0,0,0);
}

void writeV()
{
setLine(1,1,1,0,0);
setLine(0,0,0,1,0);
setLine(0,0,0,0,1);
setLine(0,0,0,1,0);
setLine(1,1,1,0,0);
setLine(0,0,0,0,0);
}

void writeW()
{
setLine(1,1,1,1,1);
setLine(0,0,0,1,0);
setLine(0,0,1,0,0);
setLine(0,0,0,1,0);
setLine(1,1,1,1,1);
setLine(0,0,0,0,0);
}

void writeX()
{
setLine(1,0,0,0,1);
setLine(0,1,0,1,0);
setLine(0,0,1,0,0);
setLine(0,1,0,1,0);
setLine(1,0,0,0,1);
setLine(0,0,0,0,0);
}

void writeY()
{
setLine(1,0,0,0,0);
setLine(0,1,0,0,0);
setLine(0,0,1,1,1);
setLine(0,1,0,0,0);
setLine(1,0,0,0,0);
setLine(0,0,0,0,0);
}

void writeZ()
{
setLine(1,0,0,0,1);
setLine(1,0,0,1,1);
setLine(1,0,1,0,1);
setLine(1,1,0,0,1);
setLine(1,0,0,0,1);
setLine(0,0,0,0,0);
}

void writeQM()
{
setLine(0,1,0,0,0);
setLine(1,0,0,0,0);
setLine(1,0,1,0,1);
setLine(1,0,1,0,0);
setLine(0,1,0,0,0);
setLine(0,0,0,0,0);	
}

void writeAPO()
{
setLine(1,1,0,0,0);
setLine(0,0,0,0,0);	
}

void writeEMP()
{
setLine(0,0,0,0,0);
setLine(0,0,0,0,0);
setLine(0,0,0,0,0);
setLine(0,0,0,0,0);
}

void writeEM()
{
setLine(1,1,1,0,1);
setLine(0,0,0,0,0);
}

void writeDOT()
{
setLine(0,0,0,0,1);
setLine(0,0,0,0,0);
}

void writeCOM()
{
setLine(0,0,0,1,1);
setLine(0,0,0,0,0);
}

void writeEQL()
{
setLine(0,1,0,1,0);
setLine(0,1,0,1,0);
setLine(0,1,0,1,0);
setLine(0,0,0,0,0);
}

void writeBRKO()
{
setLine(0,1,1,1,0);
setLine(1,0,0,0,1);
setLine(0,0,0,0,0);
}

void writeBRKC()
{
setLine(1,0,0,0,1);
setLine(0,1,1,1,0);
setLine(0,0,0,0,0);
}


void writer(char word[],int size)
{
fill(0x00);
	for (unsigned int i = 0; i < (size+3); i++)
{	
	char current = word[i];
	if (i >= size) current = ' ';
	switch(current)
	{case 'A':
	writeA();
	break;
	case 'B':
	writeB();
	break;
	case 'C':
	writeC();
	break;
	case 'D':
	writeD();
	break;
	case 'E':
	writeE();
	break;
	case 'F':
	writeF();
	break;
	case 'G':
	writeG();
	break;
	case 'H':
	writeH();
	break;
	case 'I':
	writeI();
break;
	case 'J':
	writeJ();
break;
	case 'K':
	writeK();
break;
	case 'L':
	writeL();
break;
	case 'M':
	writeM();
break;
	case 'N':
	writeN();
break;
	case 'O':
	writeO();
break;
	case 'P':
	writeP();
break;
	case 'Q':
	writeQ();
break;
	case 'R':
	writeR();
break;
	case 'S':
	writeS();
break;
	case 'T':
	writeT();
break;
	case 'U':
	writeU();
	break;
	case 'V':
	writeV();
	break;
	case 'W':
	writeW();
	break;
	case 'X':
	writeX();
	break;
	case 'Y':
	writeY();
	break;
	case 'Z':
	writeZ();
	break;
	case '?':
	writeQM();
	break;
	case '\'':
	writeAPO();
	break;
	case '!':
	writeEM();
	break;
	case '(':
	writeBRKO();
	break;
	case ')':
	writeBRKC();
	break;
	case '=':
	writeEQL();
	break;
	case '.':
	writeDOT();
	break;
	case ',':
	writeCOM();
	break;
	default:
	writeEMP();
	break;
	} 
}
}