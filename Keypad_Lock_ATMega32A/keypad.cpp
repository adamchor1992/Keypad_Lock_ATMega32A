#define F_CPU 1000000	//1MHz

#include "keypad.h"
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>	//header containing delay functions

Button Keypad::GetPressedButton(void)
{
	uint8_t column_value;
	
	_delay_us(DELAY_BETWEEN_ROWS_POLLING);
	
	// FIRST ROW
	/*Force low logic state on the first row*/
	PORTD &= ~(1<<0);
	_delay_us(DELAY_BETWEEN_ROWS_POLLING);

	column_value = PIND;

	if(!(column_value & 1<<4))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_1;
	}
	else if(!(column_value & 1<<5))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_2;
	}
	else if(!(column_value & 1<<6))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_3;
	}
	else if(!(column_value & 1<<7))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_4;
	}

	PORTD |= (1<<0); // 1 on first row;
	
	_delay_us(DELAY_BETWEEN_ROWS_POLLING);
	
	// SECOND ROW
	/*Force low logic state on the second row*/
	PORTD &= ~(1<<1);
	_delay_us(DELAY_BETWEEN_ROWS_POLLING);

	column_value = PIND;

	if(!(column_value & 1<<4))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_5;
	}
	else if(!(column_value & 1<<5))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_6;
	}
	else if(!(column_value & 1<<6))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_7;
	}
	else if(!(column_value & 1<<7))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_8;
	}

	PORTD |= (1<<1); // 1 on second row;

	_delay_us(DELAY_BETWEEN_ROWS_POLLING);

	// THIRD ROW
	/*Force low logic state on the third row*/
	PORTD &= ~(1<<2);
	_delay_us(DELAY_BETWEEN_ROWS_POLLING);

	column_value = PIND;

	if(!(column_value & 1<<4))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_9;
	}
	else if(!(column_value & 1<<5))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_0;
	}
	else if(!(column_value & 1<<6))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_ERASE_DIGIT;
	}
	else if(!(column_value & 1<<7))
	{
		while(1)
		{
			if(PIND!=column_value)
			break;
		}
		_delay_ms(DELAY_AFTER_BUTTON_PRESS_DETECTED);
		return Button::BUTTON_OK;
	}

	PORTD |= (1<<2);

	_delay_us(DELAY_BETWEEN_ROWS_POLLING);

	return Button::NO_BUTTON_PRESSED;
}