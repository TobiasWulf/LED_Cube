/*
 *  Project: EesteCube (5x5x5)
 *  simple_draw.c
 *
 *  Created: 17.12.2011 13:58:32
 *  Author: Tobias Wulf
 *  
 *  GPL lisence
 */
 
#include <math.h>
#include "cube.h"



// Voxel comes from volumetric and pixel. It describes a data point of 3D grid graphic
// Voxel == 1 LED in the 3D cube grid
// Set a voxel (LED) in the cube buffer

void setLED(int x, int y, int z)
{ 
	if (inrange(x, y, z)) cube[z][y] |= (1 << x);
}

// Clear a voxel (LED) in the cube buffer
void clrLED(int x, int y, int z)
{
	if (inrange(x, y, z)) cube[z][y] &= ~(1 << x);
}

// Get the current status of a LED
unsigned char getLED(int x, int y, int z)
{
	if (inrange(x, y, z)){
		if (cube[z][y] & (1 << x)){
			return 0x01;
		} 
		else{
			return 0x00;
		}
	}
	else{
		return 0x00;
	}
}

// This function validates that we are drawing inside the cube.
unsigned char inrange(int x, int y, int z)
{
	if (x >= 0 && x < 5 && y >= 0 && y < 5 && z >= 0 && z < 5){
		return 0x01;
	} 
	else{
		// One of the coordinates was outside the cube.
		return 0x00;
	}
}

// Alter the state of  a voxel in the cube buffer
// This function was made in order to make set and clr versions
// of other functions without writing two almost identical functions
void alterLED(int x, int y, int z, int state)
{
	if (state == 1){
		setLED(x,y,z);
	} 
	else{
		clrLED(x,y,z);
	}
}

// Flip the state of a LED.
// If the voxel in the buffer is 1, its turned into a 0, and vice versa.
void flpLED(int x, int y, int z)
{
	if (inrange(x, y, z)) cube[z][y] ^= (1 << x);
}

// Sets all the leds in the X and Y for a given Z
// i.e. draws a horizonal plane on a given level (z)
void setplane_z (int z)
{
	int y;
	// Loop the 5 rows on the given level and write 1 to the bits.
	for(y = 0 ; y < 5 ; y++) cube[z][y] = 0x1f;
}

// Clears all the leds on X and Y for a given Z
void clrplane_z (int z)
{
	int y;
	for(y = 0 ; y < 5 ; y++) cube[z][y] = 0x00;
}

// Sets all the leds on Y and Z for a given X
void setplane_x (int x)
{
	int z;
	int y;
	// Since coordinates along the X axis are
	// the actual bits in each row of each layer
	// We loop them all, and set the apropriate bit.
	for(z = 0 ; z < 5 ; z++){
		for(y = 0 ; y < 5 ; y++){
			// Set a bit, and shift it inwards to the right X
			cube[z][y] |= (1 << x);
		}
	}
}

// Clear all the leds on Y and Z for a given X
void clrplane_x (int x)
{
	int z;
	int y;
	for(z = 0 ; z < 5 ; z++){
		for(y = 0 ; y < 5 ; y++){
			cube[z][y] &= ~(1 << x);
		}
	}
}

// Sets all the leds on X and Z for a given Y
void setplane_y (int y)
{
	int z;
	for (z = 0 ; z < 5 ; z++) cube[z][y] = 0x1f; 
}

// Sets all the leds on X and Z for a given Y
void clrplane_y (int y)
{
	int z;
	for(z = 0 ; z < 5 ; z++) cube[z][y] = 0x00; 
}

// Set a plane using the functions above
void setplane(unsigned char plane, int i, int state)
{
	if (plane == 'x'){
		if (state > 0){
			setplane_x(i);
		} 
		else{
			clrplane_x(i);
		}
	}
	
	if (plane == 'y'){
		if (state > 0){
			setplane_y(i);
		} 
		else{
			clrplane_y(i);
		}
	}
	
	if (plane == 'z'){
		if (state > 0){
			setplane_z(i);
		} 
		else{
			clrplane_z(i);
		}
	}
}


// Draw a line along the Z axis
// state=0 clears a line of voxels,
// state=1 sets a line of voxels.
void line_z(int x, int y, int z1, int z2, int state)
{
	
	if (z1>z2){
		int tmp;
		tmp = z1;
		z1= z2;
		z2 = tmp;
	}
	int i;
	for (i=z1;i<=z2;i++){
		alterLED(x,y,i,state);
	}
}

// Draw a line along the X axis
void line_x(int z, int y, int x1, int x2, int state)
{
	if (x1>x2){
		int tmp;
		tmp = x1;
		x1= x2;
		x2 = tmp;
	}
	int i;
	for (i=x1;i<=x2;i++){
		alterLED(i,y,z,state);
	}
}

// Draw a line along the Y axis.
void line_y(int z, int x, int y1, int y2, int state)
{
	if (y1>y2){
		int tmp;
		tmp = y1;
		y1= y2;
		y2 = tmp;
	}
	int i;
	for (i=y1;i<=y2;i++){
			alterLED(x,i,z,state);
	}
}

// Draws a plane on any diagonal angle
// unsigned char anchor is the plane that is constant. ("x","y", or "z")
void drawline_plane(int x2, int y2, int x1, int y1,unsigned char anchor){
	int deltax = abs(x2 - x1);        // The difference between the x's
	int deltay = abs(y2 - y1);        // The difference between the y's
	int x = x1;                       // Start x off at the first pixel
	int y = y1;                       // Start y off at the first pixel
	int xinc1;
	int xinc2;
	int yinc1;
	int yinc2;
	int den;
	int num;
	int numadd;
	int numpixels;
	
	if (x2 >= x1){                 // The x-values are increasing
		xinc1 = 1;
		xinc2 = 1;
	}
	else{                          // The x-values are decreasing
		xinc1 = -1;
		xinc2 = -1;
	}
	
	if (y2 >= y1){                 // The y-values are increasing
		yinc1 = 1;
		yinc2 = 1;
	}
	else{                          // The y-values are decreasing
		yinc1 = -1;
		yinc2 = -1;
	}
	
	if (deltax >= deltay){         // There is at least one x-value for every y-value
		xinc1 = 0;                  // Don't change the x when numerator >= denominator
		yinc2 = 0;                  // Don't change the y for every iteration
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;         // There are more x-values than y-values
	}
	else{                          // There is at least one y-value for every x-value
		xinc2 = 0;                  // Don't change the x for every iteration
		yinc1 = 0;                  // Don't change the y when numerator >= denominator
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;         // There are more y-values than x-values
	}
	int curpixel;
	for(curpixel = 0 ; curpixel <= numpixels ; curpixel++){
		if (anchor == 'z')
		{
			// Draw the current pixels
			setLED(x, y, 4);
			setLED(x, y, 3);
			setLED(x, y, 2);
			setLED(x, y, 1);
			setLED(x, y, 0);
		}
		
		if (anchor == 'x')
		{
			// Draw the current pixels
			setLED(x, 4, y);
			setLED(x, 3, y);
			setLED(x, 2, y);
			setLED(x, 1, y);
			setLED(x, 0, y);
		}
		
		if (anchor == 'y')
		{
			// Draw the current pixels
			setLED(4, y, x);
			setLED(3, y, x);
			setLED(2, y, x);
			setLED(1, y, x);
			setLED(0, y, x);
		}
		
		num += numadd;              // Increase the numerator by the top of the fraction
		if (num >= den){             // Check if numerator >= denominator
			num -= den;               // Calculate the new numerator value
			x += xinc1;               // Change the x as appropriate
			y += yinc1;               // Change the y as appropriate
		}
		x += xinc2;                 // Change the x as appropriate
		y += yinc2;                 // Change the y as appropriate
	}
}

// Copy the temp cube onto the real cube
void tmp2cube(void)
{
	int y, z;
	for(z = 0 ; z < 5 ; z++){
		for(y = 0 ; y < 5 ; y++){
			cube[z][y] = tmpcube[z][y];
		}
	}
}

// Copy the cube into the temp buffer
void cube2tmp(void)
{
	int y, z;
	for(z = 0 ; z < 5 ; z++){
		for(y = 0 ; y < 5 ; y++){
			tmpcube[z][y] = cube[z][y];
		}
	}
}

// Fill the cube with a given pattern.
// fill(0x00); clears the cube
// fill(0x1f); lights all leds
void fill (unsigned char pattern)
{
	int z;
	int y;
	for(z = 0 ; z < 5 ; z++){
		for (y = 0 ; y < 5 ; y++){
			cube[z][y] = pattern;
		}
	}
}

void Sejla_Damir()
{
	little_cube();
	
	create_cube(2, 2, 2);
	
	
	
	
	pumping_heart();
	
	//stop()
}

void little_cube(void)
{
	static unsigned int x=0, y=0, z=0;
	unsigned int axis1, direction, iteration;
	
	for (iteration=0; iteration<50; iteration++) {
	
	create_cube(x, y, z);
	
	direction = rand() % 2;

		axis1 = rand() % 3;		
		// if 0 only x changes
		// if 1 only y changes
		// if 2 only z changes
		if(direction==0) 
		{
		if (axis1 == 0)
		{
			if (x+1<4) x++;							
			else x--;
		}
		
		else if (axis1 == 1)
		{
			if (y+1<4) y++;
			else y--;
		}
		
		else if (axis1 == 2)
		{
			if (z+1<4) z++;
			else z--;
		}
		}
		
		else 
		{
		if (axis1 == 0)
		{
			if (x>0) x--;	
			else x++;						
		}
		
		else if (axis1 == 1)
		{
			if (y>0) y--;
			else y++;
		}
		
		else if (axis1 == 2)
		{
			if (z>0) z--;
			else z++;
		}
			
		}	
	
	
	delay_ms(63);
	
	}
}

void create_cube(int x, int y, int z) 
{
	fill(0x00);

	setLED(x, y, z);
	setLED(x ,y, z+1);
	setLED(x, y+1, z);
	setLED(x,y+1,z+1);
	setLED(x+1, y, z);
	setLED(x+1 ,y, z+1);
	setLED(x+1, y+1, z);
	setLED(x+1,y+1,z+1);
}
























void pumping_heart() 
{
   int i,j;
   for(i=0;i<7;i++){
	
	fill(0x00);
	
	setLED(2,2,2);
	setLED(2,3,3);
	setLED(2,1,3);
	setLED(2,4,2);
	setLED(2,0,2);
	setLED(2,3,1);
	setLED(2,1,1);
	setLED(2,2,0);
delay_ms(100);

fill(0x00);

	setLED(2,2,2);
	setLED(2,2,0);
	setLED(2,3,3);
	setLED(2,1,3);
	setLED(2+1,4,2);
	setLED(2-1,0,2);
	setLED(2,3,1);
	setLED(2,1,1);
	
delay_ms(100);
	
fill(0x00);

	setLED(2,2,2);
	setLED(2,2,0);
	setLED(2+1,3,3);
	setLED(2-1,1,3);
	setLED(2+2,4,2);
	setLED(2-2,0,2);
	setLED(2+1,3,1);
	setLED(2-1,1,1);
delay_ms(100);
	
fill(0x00);

	setLED(2,2,2);
	setLED(2,2,0);
	setLED(2+1,3,3);
	setLED(2-1,1,3);
	setLED(2+2,4-1,2);
	setLED(2-2,0+1,2);
	setLED(2+1,3,1);
	setLED(2-1,1,1);
	
delay_ms(100);
	
	fill(0x00);

	setLED(2,2,2);
	setLED(2,2,0);
	setLED(2+1,3-1,3);
	setLED(2-1,1+1,3);
	setLED(2+2,4-2,2);
	setLED(2-2,0+2,2);
	setLED(2+1,3-1,1);
	setLED(2-1,1+1,1);
	
delay_ms(100);
	
	
	fill(0x00);

	setLED(2,2,2);
	setLED(2,2,0);
	setLED(2+1,3-1,3);
	setLED(2-1,1+1,3);
	setLED(2+2,4-3,2);
	setLED(2-2,0+3,2);
	setLED(2+1,3-1,1);
	setLED(2-1,1+1,1);
delay_ms(100);
	
	fill(0x00);

	setLED(2,2,2);
	setLED(2,2,0);
	setLED(2+1,3-2,3);
	setLED(2-1,1+2,3);
	setLED(2+2,4-4,2);
	setLED(2-2,0+4,2);
	setLED(2+1,3-2,1);
	setLED(2-1,1+2,1);
	
delay_ms(100);
	
	fill(0x00);

	setLED(2,2,2);
	setLED(2,2,0);
	setLED(2+1,3-2,3);
	setLED(2-1,1+2,3);
	setLED(2+1,4-4,2);
	setLED(2-1,0+4,2);
	setLED(2+1,3-2,1);
	setLED(2-1,1+2,1);
	
	delay_ms(100);
	
	

	}
	
	
	fill(0x00);
	for(j=0;j<5;j++)
	{
	for(i=0;i<3;i++)
	{
	
	setLED(2+i,2,2);
	setLED(2+i,3,3);
	setLED(2+i,1,3);
	setLED(2+i,4,2);
	setLED(2+i,0,2);
	setLED(2+i,3,1);
	setLED(2+i,1,1);
	setLED(2+i,2,0);
	
	setLED(2-i,2,2);
	setLED(2-i,3,3);
	setLED(2-i,1,3);
	setLED(2-i,4,2);
	setLED(2-i,0,2);
	setLED(2-i,3,1);
	setLED(2-i,1,1);
	setLED(2-i,2,0);
	
	
	
delay_ms(100);
}

for(i=2;i>=0;i--)
	{
	
	clrLED(2+i,2,2);
	clrLED(2+i,3,3);
	clrLED(2+i,1,3);
	clrLED(2+i,4,2);
	clrLED(2+i,0,2);
	clrLED(2+i,3,1);
	clrLED(2+i,1,1);
	clrLED(2+i,2,0);
	
	clrLED(2-i,2,2);
	clrLED(2-i,3,3);
	clrLED(2-i,1,3);
	clrLED(2-i,4,2);
	clrLED(2-i,0,2);
	clrLED(2-i,3,1);
	clrLED(2-i,1,1);
	clrLED(2-i,2,0);
	
	
	
delay_ms(100);
}
}

	
}




















