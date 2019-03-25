
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
void effect_rain (int iterations, int delay, int hold, int speed);
void sendvoxel_z (unsigned char x, unsigned char y, unsigned char z, int delay);
void sendplane_rand_z (unsigned char z, int delay, int wait);
void blinky(void);
void flyplane(unsigned char plane,unsigned char direction, int delay);
void loadbar(int delay);
void random_1(int iterations, int voxels, int delay);
void random_2(void);
void random_filler(int iterations, int pixels, int delay, int state);
void random_filler2 (int delay, int state);
void planeflip(unsigned char axis1, int pos1, unsigned char axis2, int pos2, int delay);
void flip_playback (int delay, unsigned char flip_x, unsigned char flip_y, unsigned char flip_z);
void boingboing(int iterations, int delay, unsigned char mode, unsigned char drawmode);
void blinky(void);
void blinky2(void);
void animateCharacter(char charletter);
void writeBlank(void);
void LCHamburg(void);
void shiftBack2(void);
void shiftLeft(void);
void writer(char word[],int size);
void Sejla_Damir(void);
void little_cube(void);
void create_cube(int x, int y, int z) ;
void pumping_heart(void); 
void effect_everything_bitches(int direction, int iterations, int delay);
void effect_rings(int direction, int iterations, int delay);
void effect_explosion(int direction, int iterations, int delay);
void grow(char Array[5][5][5], int delay);
void grow2(char Array[5][5][5], int delay);
void shrink(char Array[5][5][5], int delay);
void effect_blink(int direction, int iterations, int delay);
void dim(int intensity);
void effect_snow(int direction, int iterations, int delay);
void effect_noise(int direction, int iterations, int delay);
void effect_wasdf3(int direction, int iterations, int delay);
void effect_wasdf2(int direction, int iterations, int delay);

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
void line_z(int x, int y, int z1, int z2, int state);
void line_x(int z, int y, int x1, int x2, int state);
void line_y(int z, int x, int y1, int y2, int state);
void drawline_plane(int x2, int y2, int x1, int y1,unsigned char anchor);
void fill (unsigned char pattern);
void tmp2cube(void);
void cube2tmp(void);
void writeA(int l);
void writeB(int l);
void writeC(int l);
void writeD(int l);
void writeE(int l);
void writeF(int l);
void writeG(int l);
void writeH(int l);
void writeI(int l);
void writeJ(int l);
void writeK(int l);
void writeL(int l);
void writeM(int l);
void writeN(int l);
void writeO(int l);
void writeP(int l);
void writeQ(int l);
void writeR(int l);
void writeS(int l);
void writeT(int l);
void writeU(int l);
void writeV(int l);
void writeW(int l);
void writeX(int l);
void writeY(int l);
void writeZ(int l);
void getLetter(int letter, int l);
int letterToInt(char letter);
void setLine(int one, int two, int three, int four, int five);
void _writeA(void);
void _writeB(void);
void _writeC(void);
void _writeD(void);
void _writeE(void);
void _writeF(void);
void _writeG(void);
void _writeH(void);
void _writeI(void);
void _writeJ(void);
void _writeK(void);
void _writeL(void);
void _writeM(void);
void _writeN(void);
void _writeO(void);
void _writeP(void);
void _writeQ(void);
void _writeR(void);
void _writeS(void);
void _writeT(void);
void _writeU(void);
void _writeV(void);
void _writeW(void);
void _writeX(void);
void _writeY(void);
void _writeZ(void);
void _writeQM(void);
void _writeAPO(void);
void _writeEMP(void);
void _writeEM(void);
void _writeDOT(void);
void _writeCOM(void);
void _writeEQL(void);
void _writeBRKO(void);
void _writeBRKC(void);

