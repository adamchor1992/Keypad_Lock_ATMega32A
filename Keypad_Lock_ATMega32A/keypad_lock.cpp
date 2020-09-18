#define F_CPU 1000000

#include "keypad_lock.h"
#include "digit_value.h"
#include <avr/io.h>
#include <util/delay.h>	 //header containing delay functions

KeypadLock::KeypadLock()
{
	InitPorts();
	
	m_PasswordState = PasswordState::PasswordNotSet;
}

void KeypadLock::Execute()
{
	if(m_PasswordState == PasswordState::PasswordNotSet)
	{
		UserSetsCode();
		m_PasswordState = PasswordState::PasswordSet;
		m_Display.SetAllDigitsToValue(DigitValue::LETTER_X);
	}
	else if(m_PasswordState == PasswordState::PasswordSet)
	{
		CompareEnteredCodeWithAdminCode();
		m_PasswordState = PasswordState::PasswordNotSet;
		m_Display.SetAllDigitsToValue(DigitValue::HYPHEN);
	}
}

void KeypadLock::InitPorts()
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

void KeypadLock::UserSetsCode()
{
	Button pressedButton = Button::NO_BUTTON_PRESSED;
	uint8_t digitPointer = 1;
	
	while (1)
	{
		pressedButton = m_Keypad.GetPressedButton();

		if(pressedButton != Button::NO_BUTTON_PRESSED)
		{
			if(pressedButton == Button::BUTTON_ERASE_DIGIT)
			{
				if(digitPointer > 1)
				{
					digitPointer--;
					m_Display.SetDigitValue(digitPointer, DigitValue::HYPHEN);
				}

				continue;
			}
			
			if(digitPointer == 5 && pressedButton == Button::BUTTON_OK)
			{
				m_PasswordSet[0] = m_Display.GetDigitValue(0);
				m_PasswordSet[1] = m_Display.GetDigitValue(1);
				m_PasswordSet[2] = m_Display.GetDigitValue(2);
				m_PasswordSet[3] = m_Display.GetDigitValue(3);
				
				return;
			}
			
			if(digitPointer < 5 && pressedButton != Button::BUTTON_OK)
			{
				m_Display.SetDigitValue(digitPointer, static_cast<DigitValue>(pressedButton));
				digitPointer++;
			}
		}

		if(digitPointer < 6)
		{
			m_Display.MultiplexDigits();
		}
	}
}

void KeypadLock::CompareEnteredCodeWithAdminCode()
{
	Button pressedButton = Button::NO_BUTTON_PRESSED;
	uint8_t digitPointer = 1;
	
	while (1)
	{
		pressedButton = m_Keypad.GetPressedButton();

		if(pressedButton != Button::NO_BUTTON_PRESSED)
		{
			if(pressedButton == Button::BUTTON_ERASE_DIGIT)
			{
				if(digitPointer > 1)
				{
					digitPointer--;
					m_Display.SetDigitValue(digitPointer, DigitValue::LETTER_X);
				}
				
				continue;
			}
			
			uint8_t enteredPassword[4] = {0};
			
			if(digitPointer == 5 && pressedButton == Button::BUTTON_OK)
			{
				enteredPassword[0] = m_Display.GetDigitValue(0);
				enteredPassword[1] = m_Display.GetDigitValue(1);
				enteredPassword[2] = m_Display.GetDigitValue(2);
				enteredPassword[3] = m_Display.GetDigitValue(3);
				
				if(enteredPassword[0] == m_PasswordSet[0] && enteredPassword[1] == m_PasswordSet[1] && enteredPassword[2] == m_PasswordSet[2] && enteredPassword[3] == m_PasswordSet[3])
				{
					/*Password correct*/
					m_Display.SetDigitValue(1, DigitValue::DIGIT_0);
					m_Display.SetDigitValue(2, DigitValue::LETTER_P);
					m_Display.SetDigitValue(3, DigitValue::LETTER_E);
					m_Display.SetDigitValue(4, DigitValue::LETTER_n);
					
					ShortDelay();
					
					return;
				}
				else
				{
					/*Wrong password*/
					m_Display.SetDigitValue(1, DigitValue::LETTER_b);
					m_Display.SetDigitValue(2, DigitValue::LETTER_A);
					m_Display.SetDigitValue(3, DigitValue::LETTER_d);
					m_Display.SetDigitValue(4, DigitValue::EMPTY);
					
					ShortDelay();
					
					m_Display.SetAllDigitsToValue(DigitValue::LETTER_X);
					
					digitPointer = 1;
					
					continue;
				}
			}
			
			if(digitPointer < 5 && pressedButton != Button::BUTTON_OK)
			{
				m_Display.SetDigitValue(digitPointer, static_cast<DigitValue>(pressedButton));
				digitPointer++;
			}
		}

		if(digitPointer < 6)
		{
			m_Display.MultiplexDigits();
		}
	}
}

void KeypadLock::ShortDelay()
{
	int delay = 0;
	
	while(1)
	{
		m_Display.MultiplexDigits();
		
		_delay_ms(5);
		delay++;

		if(delay >= 200) //if about 1 second passed
		{
			break;
		}
	}
}