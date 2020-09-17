#define F_CPU 1000000	//1MHz

#include "display.h"
#include <avr/io.h>
#include <util/delay.h>	//header containing delay functions

void Display::SetDigit(uint8_t number, uint8_t position)
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
	Clear();
}

void Display::SetValueOnWholeDisplay(uint8_t value, uint8_t displayed_values[])
{
	for(int i=0; i<4; i++)
	{
		displayed_values[i] = value;
	}
}

void Display::Clear()
{
	PORTA = 255;
	PORTB = 255;
}