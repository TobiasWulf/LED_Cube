/*
 *  Project: EesteCube (5x5x5)
 *  main.c
 *
 *  Created: 17.12.2011 13:58:32
 *  Author: Tobias Wulf
 *  
 *  GPL lisence
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "cube.h"
#include "stdlib.h"

// functions in main.c

int main(void)
{

	//Set the layer and Y row to start drawing at
	current_layer = 0x00;
	current_Yrow = 0x00;
	//Set effect to start with
	current_effect = 0;
 	
	cube_ini();

	boot_check(500);
	
	while(1)
    {
		launch_effect(current_effect);
    }
}

void delay_ms(int delay)
{
	int i;
	for(i = 0 ; i < delay ; i++) _delay_ms(1);
}

void cube_ini()
{
	
	//set Input and Output for data direction
	//output = 1
	//input = 0
	DDRA = 0xff; //set X_PORT for output 00011111
	DDRB = 0x00; //set BUTTON_PORT for input and ISP
	DDRC = 0xff; //set Y_PORT for output 00011111
	DDRD = 0xff; //set Z/EN_PORT for output 11111100 and RXD/TXD for serial in (needs to enable with USRB)
	
	X_PORT = 0x00;
	Y_PORT = 0x00;
	Z_PORT = 0x00;
	//set the intern pull ups where needed
	BUTTON_PORT |= (1 << BUTTON);
	
	// enable LED drivers
	EN_PORT &= ~(1 << EN);

	// define Mask for output register in ISR
	_X_[0] = 0x01;
	_X_[1] = 0x02;
	_X_[2] = 0x04;
	_X_[3] = 0x08;
	_X_[4] = 0x10;

	_Y_[0] = 0x10;
	_Y_[1] = 0x08;
	_Y_[2] = 0x04;
	_Y_[3] = 0x02;
	_Y_[4] = 0x01;

	_Z_[0] = 0x04;
	_Z_[1] = 0x08;
	_Z_[2] = 0x10;
	_Z_[3] = 0x20;
	_Z_[4] = 0x40;

	// ##########Initiate timers and external interrupt############

	
	//Frame buffer interrupt Timer Counter Control Register in CTC mode enabled in Timer Interrupt Mask Register
	TCNT0 = 0x00; //initial counter value = 0
	TIMSK |= (1 << OCIE0);  //Enable CTC interrupt

	// Every 256th cpu cycle, a counter is incremented.
	// Every time that counter reaches 10, it is reset to 0,
	// and the interrupt routine is executed.
	// 16000000/256/10 = 6250 times per second
	// There are 5 rows per layer to update..
	// 16000000/256/10/5/5 = 250 FPS
	
	OCR0 = 10; //Interrupt at counter = 10
	TCCR0 |= (1 << CS02); //prescaler = 256
	TCCR0 |= (1 << WGM01); // Clear Timer on Compare Match (CTC) mode

	//Ext. interrupt on interrupt pin INT2 (PB2) for effect switching
	GICR |= (1 << INT2); // INT2 enable im General Interrupt Control Register
	MCUCSR &= ~(1 << ISC2); //Execute interrupt with falling edge

	//Activate global interrupts
	sei();
}

//Interrupt Service Routine for Frame Buffer
ISR(TIMER0_COMP_vect)
{
	

	//Enable the layer
	Z_PORT = _Z_[current_layer];
	
		for(current_Yrow = 0 ; current_Yrow < 5 ; current_Yrow++){	
			X_PORT = cube[current_layer][current_Yrow];
			Y_PORT = _Y_[current_Yrow];
		}
 
	
	//Running through 1 layer wins vs. updating all layers during an interrupt.
	//Because the ISR comes faster to an end and the cube has a faster update cycle to the buffer.
	if(current_layer++ == 4) current_layer = 0;
}

//Interrupt Service Routine for effect switching
ISR(INT2_vect)
{

	if(current_effect++ == 2) current_effect = 0;

}

void boot_check(int delay)
{
	//shows that the cube was successfully initiated
	//earn some blink blink for that ;)
	int i;
	
	for(i = 0 ; i < 4 ; i++)
	{
		fill(0x1f);
		delay_ms(delay);
		fill(0x00);
		delay_ms(delay);
	}

}

void launch_effect(unsigned char choice)
{

	switch(choice)
	{
		case 0:
		
		Sejla_Damir();
		
		break;
		
		case 1:
		
		effect_spiral(1,10,100);

		break;
		
		case 2:
		
		effect_spinning_plane(1,10,100);

		break;
		
		// etc.
	}
}
