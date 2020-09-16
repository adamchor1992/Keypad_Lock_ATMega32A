#define F_CPU 1000000												//1MHz

#include <util/delay.h>	 //header containing delay functions
#include <avr/io.h> 
#include "functions.h"

void init_ports(void)
{
	reset_ports();
	clear_display();
	
	DDRA = 255;									//output_port_A driving 7 segment display
	DDRB |= (1<<0) | (1<<1) | (1<<2) | (1<<3);  //PORT0, PORT1, PORT2, PORT3 driving 7 segment display

	DDRD |= (1<<0)|(1<<1)|(1<<2)|(1<<3);		//PIN0,PIN1,PIN2,PIN3 set as output, rest as input
	
	PORTD=255;									//set whole PORT to 1 (INVERSE LOGIC)
	
	PORTD |= (1<<4)|(1<<5)|(1<<6)|(1<<7);		//pull-up on input PINS of PORTD
}

void reset_ports(void)
{
	DDRA = 0;
	DDRB = 0;
	DDRC = 0;
	DDRD = 0;
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
}

void set_display(uint8_t number, uint8_t position)
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

void set_value_on_whole_display(uint8_t value, uint8_t displayed_values[])
{
	int i=0;
	for(i=0; i<4;i++)
	{
		*(displayed_values + i) = value;
	}
}

void clear_display(void)
{
	PORTA = 255;
	PORTB = 255;
}

uint8_t select_number(void)
{
	uint8_t column_value;
	
	// FIRST ROW

	_delay_us(200);
	PORTD &= ~(1<<0); // 0 on first row;
	_delay_us(200);

	column_value = PIND;

	if(!(column_value & 1<<4))
	{
		//1
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 1;
	}
	else if(!(column_value & 1<<5))
	{
		//2
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 2;
	}
	else if(!(column_value & 1<<6))
	{
		//3
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 3;
	}
	else if(!(column_value & 1<<7))
	{
		//4
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 4;
	}

	PORTD |= (1<<0); // 1 on first row;
	
	_delay_us(200);

	// SECOND ROW

	PORTD &= ~(1<<1); // 0 on second row;
	_delay_us(200);

	column_value = PIND;

	if(!(column_value & 1<<4))
	{
		//5
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 5;
	}
	else if(!(column_value & 1<<5))
	{
		//6
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 6;
	}
	else if(!(column_value & 1<<6))
	{
		//7
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 7;
	}
	else if(!(column_value & 1<<7))
	{
		//8
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 8;
	}

	PORTD |= (1<<1); // 1 on second row;

	_delay_us(200);

	// THIRD ROW
	
	PORTD &= ~(1<<2); // 0 on third row;
	_delay_us(200);

	column_value = PIND;

	if(!(column_value & 1<<4))
	{
		//9
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 9;
	}
	else if(!(column_value & 1<<5))
	{
		//0
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 0;
	}
	else if(!(column_value & 1<<6))
	{
		//OK
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 11;
	}
	else if(!(column_value & 1<<7))
	{
		//CANCEL
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(100);
		return 12;
	}

	PORTD |= (1<<2); // 0 on third row;

	_delay_us(200);

	return 200;      //reserved value meaning that input did not change
}