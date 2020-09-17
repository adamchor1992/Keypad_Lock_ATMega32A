#define F_CPU 1000000

#include "keypad_lock.h"
#include <avr/io.h>
#include <util/delay.h>	 //header containing delay functions

KeypadLock::KeypadLock()
{
	InitPorts();
	
	m_PasswordState = PasswordState::PasswordNotSet;
	
	UserSetsCode();
	
	m_Display.SetAllDigitsToValue(13);										//set display to '-.' in locked state
	
	CompareEnteredCodeWithAdminCode();
	
	while(1)
	{
		m_Display.MultiplexDigits();
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
	
	//SETTING CODE FOR FIRST TIME
	while (1)
	{
		pressedButton = m_Keypad.GetPressedButton();							//poll for value on keypad

		if(pressedButton != Button::NO_BUTTON_PRESSED)				//if input changed
		{
			if(pressedButton == Button::BUTTON_CANCEL)								//if cancel button was pressed
			{
				m_Display.SetAllDigitsToValue('-');
				digitPointer = 1;
				continue;
			}
			
			if(digitPointer == 5 && pressedButton == Button::BUTTON_OK)						//if 4 digits were entered and OK button was pressed
			{
				m_Password[0] = m_Display.GetDigitValue(0);
				m_Password[1] = m_Display.GetDigitValue(1);
				m_Password[2] = m_Display.GetDigitValue(2);
				m_Password[3] = m_Display.GetDigitValue(3);
				break;
			}
			
			m_Display.SetDigitValue(digitPointer-1, static_cast<uint8_t>(pressedButton));
			digitPointer++;
		}

		if(digitPointer < 6)
		{
			m_Display.MultiplexDigits();
		}
		else
		{
			m_Display.SetAllDigitsToValue('-');
			digitPointer = 1;
		}
	}
}

void KeypadLock::CompareEnteredCodeWithAdminCode()
{
	Button pressedButton = Button::NO_BUTTON_PRESSED;
	uint8_t digitPointer = 1;
	
	//COMPARING ENTERED CODE WITH CODE SET BEFORE
	while (1)
	{
		pressedButton = m_Keypad.GetPressedButton();							//poll for value on keypad

		if(pressedButton != Button::NO_BUTTON_PRESSED)									//if input changed
		{
			if(pressedButton == Button::BUTTON_CANCEL)								//if cancel button was pressed
			{
				m_Display.SetAllDigitsToValue(13);
				digitPointer=1;
				continue;
			}
			
			uint8_t enteredPassword[4] = {0};										//table storing code entered by user
			
			if(digitPointer==5 && pressedButton == Button::BUTTON_OK)						//if 4 digits were entered and OK button was pressed
			{
				enteredPassword[0] = m_Display.GetDigitValue(0);
				enteredPassword[1] = m_Display.GetDigitValue(1);
				enteredPassword[2] = m_Display.GetDigitValue(2);
				enteredPassword[3] = m_Display.GetDigitValue(3);
				
				if(enteredPassword[0] == m_Password[0] && enteredPassword[1] == m_Password[1] && enteredPassword[2] == m_Password[2] && enteredPassword[3] == m_Password[3]) //check if code is correct
				{
					m_Display.SetDigitValue(0, 0);	//O
					m_Display.SetDigitValue(1, 14);	//P
					m_Display.SetDigitValue(2, 15);	//E
					m_Display.SetDigitValue(3, 16);	//N
					break;
				}
				else
				{
					m_Display.SetDigitValue(0, 8);	//B
					m_Display.SetDigitValue(1, 17);	//A
					m_Display.SetDigitValue(2, 0);	//D
					m_Display.SetDigitValue(3, 18);	//nothing
					
					long int delay = 0;
					
					while(1)
					{
						m_Display.MultiplexDigits();
						
						_delay_ms(5);
						delay++;

						if(delay >= 200) //if about 1 second passed
						{
							m_Display.SetAllDigitsToValue(13);
							digitPointer = 1;
							break;
						}
					}
					continue;
				}
			}

			m_Display.SetDigitValue(digitPointer-1, static_cast<uint8_t>(pressedButton));
			digitPointer++;
		}

		if(digitPointer<6)
		{
			m_Display.MultiplexDigits();
		}
		else
		{
			m_Display.SetAllDigitsToValue('-');
			digitPointer = 1;
		}
	}
}