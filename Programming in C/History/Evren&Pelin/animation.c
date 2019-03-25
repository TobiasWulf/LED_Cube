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
	{ 0x1F, 0x02, 0x04, 0x08, 0x08 },
	{ 0x08, 0x08, 0x04, 0x02, 0x02 },
};

const unsigned char spinning_line2[6][5] PROGMEM =
{
	
	
	{ 0x1F, 0x11, 0x11, 0x11, 0x1F },
	{ 0x1F, 0x11, 0x11, 0x11, 0x1F },
	{ 0x1F, 0x11, 0x11, 0x11, 0x1F },
	{ 0x1F, 0x11, 0x11, 0x11, 0x1F },
	{ 0x1F, 0x11, 0x11, 0x11, 0x1F },
	{ 0x1F, 0x11, 0x11, 0x11, 0x1F },
};


const unsigned char andLine[6][5] PROGMEM =
{
	
	{ 0x00, 0x00, 0x00, 0x00, 0x0F },
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },
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
			cube[z][0] = pgm_read_byte(&spinning_line[(i+z)%6][4]);
			cube[z][1] = pgm_read_byte(&spinning_line[(i+z)%6][3]);
			cube[z][2] = pgm_read_byte(&spinning_line[(i+z)%6][2]);
			cube[z][3] = pgm_read_byte(&spinning_line[(i+z)%6][1]);
			cube[z][4] = pgm_read_byte(&spinning_line[(i+z)%6][0]);
			// the +z makes the animation iterate one step for each plane
			// making it into a spiral
		}
		delay_ms(delay);
	}
}






// Shows an animation of a spinning spiral
void uptodown(int direction, int iterations, int delay)
{
	int i,j,k, h;
	int x=0,y,z,t;		// cube level
	int a = 1, b;
	char temp [5][5];
	
	
	if(direction==0 ){
	for(i = 0; i < 5; i++){
	for(j = 0; j < 5; j++){
	for(k = 0; k < 5; k++){
	
		setLED(i,j,k);
		delay_ms(delay);
		//clrLED(i,j,k);
		
	}
	}
	}
	x++;
	}
	
	clrLED(0,0,0);
	clrLED(0,0,1);
	clrLED(0,0,2);
	clrLED(0,0,3);
	clrLED(0,0,4);
	clrLED(0,1,4);
	clrLED(0,1,2);
	clrLED(0,2,3);
	x=1;
	
	
	
	/*
	for(i = 4; i > -1; i--){
	for(j = 4; j > -1; j--){
	for(k = 4; k > -1; k--){
	
		clrLED(j,k,i);
		delay_ms(delay);
		
		
	}
	}
	}
	*/
	
	
	
	
	/*
	setLED(1,1,4);
		
	setLED(1,2,4);
	
	setLED(1,3,4);
	
	setLED(2,1,4);
	
	setLED(2,2,4);
	
	setLED(2,3,4);
	
	setLED(3,1,4);
	
	setLED(3,2,4);
	
	setLED(3,3,4);
	*/

	
			// Loop cube levels
		/*for (z=0;z<5;z++)
		{
			// Read the animation from program memory and put it in the cube buffer.
			// y=0 and y=2 is stored in the upper nibble of the byte, and must be bitshifted into place.
			
			
			
			cube[z][0] = pgm_read_byte(&spinning_line2[(i+z)%6][0]);
			cube[z][1] = pgm_read_byte(&spinning_line2[(i+z)%6][1]);
			cube[z][2] = pgm_read_byte(&spinning_line2[(i+z)%6][2]);
			cube[z][3] = pgm_read_byte(&spinning_line2[(i+z)%6][3]);
			cube[z][4] = pgm_read_byte(&spinning_line2[(i+z)%6][4]);
			// the +z makes the animation iterate one step for each plane
			// making it into a spiral
			

			
		}
		*/
		
		
		
		
		
		
		

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

