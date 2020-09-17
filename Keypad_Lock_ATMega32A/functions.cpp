#define F_CPU 1000000	//1MHz

#include <util/delay.h>	//header containing delay functions
#include <avr/io.h>
#include "functions.h"

void init_ports(void)
{
	/*----------------------PORTA----------------------*/
	/*All 8 pins of PORTA set as output drive segments of 7 segment display*/
	DDRA = 255;
	PORTA = 0;

	/*----------------------PORTB----------------------*/
	/*Pins PIN0, PIN1, PIN2, PIN3 of PORTB set as output drive digits of 7 segment display,
	rest of pins of PORTB is unused*/
	DDRB = 0;
	DDRB |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3);
	PORTB = 0;

	/*----------------------PORTD----------------------*/
	/*Pins PIN0, PIN1, PIN2, PIN3 of PORTD set as output drive rows of keyboard*/
	DDRD |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3);
	/*Pins PIN4, PIN5, PIN6, PIN7 of PORTD set as input control columns of keyboard*/
	DDRD |= (0 << PIN4) | (0 << PIN5) | (0 << PIN6) | (0 << PIN7);
	/*Pull-up on input PINS of PORTD*/
	PORTD |= (1<<4)|(1<<5)|(1<<6)|(1<<7);
}

void setDigit(uint8_t number, uint8_t position)
{
	switch(position)
	{
		case 1:
		PORTB &= ~(1<<0);
		break;

		case 2:
		PORTB &= ~(1<<1);
		break;

		case 3:
		PORTB &= ~(1<<2);
		break;

		case 4:
		PORTB &= ~(1<<3);
		break;
	}

	switch(number)
	{
		/*Hex codes for common anode 7-segment display setup*/
		case 0:
		PORTA = 0xC0;
		break;

		case 1:
		PORTA = 0xF9;
		break;

		case 2:
		PORTA = 0xA4;
		break;

		case 3:
		PORTA = 0xB0;
		break;

		case 4:
		PORTA = 0x99;
		break;

		case 5:
		PORTA = 0x92;
		break;

		case 6:
		PORTA = 0x82;
		break;
		
		case 7:
		PORTA = 0xF8;
		break;

		case 8:
		PORTA = 0x80;
		break;

		case 9:
		PORTA = 0x90;
		break;
		
		case '-':      // display '-'
		PORTA = 0xBF;
		break;
		
		case '.':	  // display '.'
		PORTA = 0x7F;
		break;
		
		case 13:
		PORTA = 0x3F; // display '-' and '.' simultaneously
		break;
		
		case 14:
		PORTA = 0x8C; // letter P
		break;
		
		case 15:
		PORTA = 0x86; // letter E
		break;
		
		case 16:
		PORTA = 0xC8; // letter N
		break;
		
		case 17:
		PORTA = 0x88;  //  letter A
		break;
		
		case 18:
		PORTA = 0xFF;  //display nothing
		break;
	}
	
	_delay_us(600);
	clear_display();
}

void setValueOnWholeDisplay(uint8_t value, uint8_t displayed_values[])
{
	for(int i=0; i<4; i++)
	{
		displayed_values[i] = value;
	}
}

void clear_display(void)
{
	PORTA = 255;
	PORTB = 255;
}