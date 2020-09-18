#define F_CPU 1000000 /*1MHz*/

#include "display.h"
#include <avr/io.h>
#include <util/delay.h>

Display::Display()
{
	m_DigitValues[0] = DigitValue::HYPHEN;
	m_DigitValues[1] = DigitValue::HYPHEN;
	m_DigitValues[2] = DigitValue::HYPHEN;
	m_DigitValues[3] = DigitValue::HYPHEN;
}

void Display::SetDigit(Position position, DigitValue digitValue)
{
	switch(position)
	{
		case Position::POSITION_1:
		PORTB &= ~(1<<0);
		break;

		case Position::POSITION_2:
		PORTB &= ~(1<<1);
		break;

		case Position::POSITION_3:
		PORTB &= ~(1<<2);
		break;

		case Position::POSITION_4:
		PORTB &= ~(1<<3);
		break;
	}

	switch(digitValue)
	{
		/*Hex codes for common anode 7-segment display setup*/
		case DigitValue::DIGIT_0:
		PORTA = 0xC0;
		break;

		case DigitValue::DIGIT_1:
		PORTA = 0xF9;
		break;

		case DigitValue::DIGIT_2:
		PORTA = 0xA4;
		break;

		case DigitValue::DIGIT_3:
		PORTA = 0xB0;
		break;

		case DigitValue::DIGIT_4:
		PORTA = 0x99;
		break;

		case DigitValue::DIGIT_5:
		PORTA = 0x92;
		break;

		case DigitValue::DIGIT_6:
		PORTA = 0x82;
		break;
		
		case DigitValue::DIGIT_7:
		PORTA = 0xF8;
		break;

		case DigitValue::DIGIT_8:
		PORTA = 0x80;
		break;

		case DigitValue::DIGIT_9:
		PORTA = 0x90;
		break;
		
		case DigitValue::HYPHEN:
		PORTA = 0xBF;
		break;
		
		case DigitValue::DOT:
		PORTA = 0x7F;
		break;
		
		case DigitValue::HYPHEN_WITH_DOT:
		PORTA = 0x3F;
		break;
		
		case DigitValue::LETTER_P:
		PORTA = 0x8C;
		break;
		
		case DigitValue::LETTER_E:
		PORTA = 0x86;
		break;
		
		case DigitValue::LETTER_n:
		PORTA = 0xAB;
		break;
		
		case DigitValue::LETTER_b:
		PORTA = 0x83;
		break;
				
		case DigitValue::LETTER_A:
		PORTA = 0x88;
		break;
		
		case DigitValue::LETTER_d:
		PORTA = 0xA1;
		break;
		
		case DigitValue::EMPTY:
		PORTA = 0xFF;
		break;
	}
	
	_delay_us(600);
	Clear();
}

void Display::SetAllDigitsToValue(DigitValue digitValue)
{
	for(int i=0; i < 4; i++)
	{
		m_DigitValues[i] = digitValue;
	}
}

void Display::MultiplexDigits()
{
	SetDigit(Position::POSITION_1, m_DigitValues[0]);
	SetDigit(Position::POSITION_2, m_DigitValues[1]);
	SetDigit(Position::POSITION_3, m_DigitValues[2]);
	SetDigit(Position::POSITION_4, m_DigitValues[3]);
}

void Display::SetDigitValue(uint8_t position, DigitValue digitValue)
{
	m_DigitValues[position - 1] = digitValue;
}

uint8_t Display::GetDigitValue(uint8_t digit) 
{
	return static_cast<uint8_t>(m_DigitValues[digit]);
}

void Display::Clear()
{
	PORTA = 255;
	PORTB = 255;
}