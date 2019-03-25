
/*
 *  Project: EesteCube (5x5x5)
 *  cube.h
 *
 *  Created: 17.12.2011 13:58:32
 *  Author: Tobias Wulf
 *  
 *  GPL lisence
 */ 

#ifndef Cube
#define Cube
#endif

// Define CPU Speed
#define FOSC 16000000
#define BAUD 9600

/*Define Bits, Ports*/

#define OFF 0x00 

// Define mask for LED grid
volatile unsigned char _Y_[5];
#define Y_PORT PORTC
volatile unsigned char _X_[5];
#define X_PORT PORTA

// Define masks for the layer select
volatile unsigned char _Z_[5];
#define Z_PORT PORTD

// Define pin and port for LED driver enable
#define EN PD7
#define EN_PORT PORTD

// Define button for effect switching
#define BUTTON PB2
#define BUTTON_PORT PORTB



// *** Cube buffer ***
// The 3D image displayed on the cube is buffered in a 2d array 'cube'.
// The 1st dimension in this array is the Z axis of the cube.
// The 2nd dimension of the array is the Y axis.
// Each byte is a stripe of leds running along the X axis at the given
// Z and Y coordinates.
// "volatile" makes the variables reachable from within the interrupt functions
volatile unsigned char cube[5][5];

// We sometimes want to draw into a temporary buffer so we can modify it
// before writing it to the cube buffer.
// e.g. invert, flip, reverse the cube..
volatile unsigned char tmpcube[5][5];

// What layer the interrupt routine is currently showing.
volatile unsigned char current_layer;

// What Y row (LED driver) will be set in the current layer
volatile unsigned char current_Yrow;

// Choice of current effect. Incremented by ext. interrubt
unsigned char current_effect;

// System function in main.c
void cube_ini(void);
void boot_check(int delay);
void launch_effect(unsigned char choice);
void delay_ms(int delay);

// functions in animation.c
void effect_spiral(int direction, int iterations, int delay);
void effect_spinning_plane(int direction, int iterations, int delay);

// functions in simple_draw.c
void setLED(int x, int y, int z);
void clrLED(int x, int y, int z);
unsigned char getLED(int x, int y, int z);
unsigned char inrange(int x, int y, int z);
void flpLED(int x, int y, int z);
void alterLED(int x, int y, int z, int state);
void setplane_z(int z);
void clrplane_z(int z);
void setplane_x(int x);
void clrplane_x(int x);
void setplane_y(int y);
void clrplane_y(int y);
void setplane(unsigned char plane, int i, int state);
void setline_z(int x, int y, int z1, int z2);
void setline_x(int z, int y, int x1, int x2);
void setline_y(int z, int x, int y1, int y2);
void clrline_z(int x, int y, int z1, int z2);
void clrline_x(int z, int y, int x1, int x2);
void clrline_y(int z, int x, int y1, int y2);
void drawline_plane(int x2, int y2, int x1, int y1,unsigned char anchor);
void fill (unsigned char pattern);
void tmp2cube(void);
void cube2tmp(void);
