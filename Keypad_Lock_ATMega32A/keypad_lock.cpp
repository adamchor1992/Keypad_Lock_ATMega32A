#define F_CPU 1000000

#include "keypad_lock.h"
#include <avr/io.h>
#include <util/delay.h>	 //header containing delay functions

KeypadLock::KeypadLock()
{
	InitPorts();
	
	UserSetsCode(password);
	
	display.SetAllDigitsToValue(13);										//set display to '-.' in locked state
	
	CompareEnteredCodeWithAdminCode(enteredPassword, password);
	
	while(1)
	{
		display.MultiplexDigits();
	}
}

void KeypadLock::InitPorts(void)
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

void KeypadLock::UserSetsCode(uint8_t * code)
{
	Button pressedButton = Button::NO_BUTTON_PRESSED;
	uint8_t digitPointer = 1;
	
	//SETTING CODE FOR FIRST TIME
	while (1)
	{
		pressedButton = keypad.GetPressedButton();							//poll for value on keypad

		if(pressedButton != Button::NO_BUTTON_PRESSED)				//if input changed
		{
			if(pressedButton == Button::BUTTON_CANCEL)								//if cancel button was pressed
			{
				display.SetAllDigitsToValue('-');
				digitPointer = 1;
				continue;
			}
			
			if(digitPointer == 5 && pressedButton == Button::BUTTON_OK)						//if 4 digits were entered and OK button was pressed
			{
				code[0] = display.GetDigitValue(0);
				code[1] = display.GetDigitValue(1);
				code[2] = display.GetDigitValue(2);
				code[3] = display.GetDigitValue(3);
				break;
			}
			
			display.SetDigitValue(digitPointer-1, static_cast<uint8_t>(pressedButton));
			digitPointer++;
		}

		if(digitPointer < 6)
		{
			display.MultiplexDigits();
		}
		else
		{
			display.SetAllDigitsToValue('-');
			digitPointer = 1;
		}
	}
}

void KeypadLock::CompareEnteredCodeWithAdminCode(uint8_t * enteredCode, uint8_t * code)
{
	Button pressedButton = Button::NO_BUTTON_PRESSED;
	uint8_t digitPointer = 1;
	
	//COMPARING ENTERED CODE WITH CODE SET BEFORE
	while (1)
	{
		pressedButton = keypad.GetPressedButton();							//poll for value on keypad

		if(pressedButton != Button::NO_BUTTON_PRESSED)									//if input changed
		{
			if(pressedButton == Button::BUTTON_CANCEL)								//if cancel button was pressed
			{
				display.SetAllDigitsToValue(13);
				digitPointer=1;
				continue;
			}
			
			if(digitPointer==5 && pressedButton == Button::BUTTON_OK)						//if 4 digits were entered and OK button was pressed
			{
				enteredCode[0] = display.GetDigitValue(0);
				enteredCode[1] = display.GetDigitValue(1);
				enteredCode[2] = display.GetDigitValue(2);
				enteredCode[3] = display.GetDigitValue(3);
				
				if(enteredCode[0]==code[0] && enteredCode[1]==code[1] && enteredCode[2]==code[2] && enteredCode[3]==code[3]) //check if code is correct
				{
					display.SetDigitValue(0, 0);	//O
					display.SetDigitValue(1, 14);	//P
					display.SetDigitValue(2, 15);	//E
					display.SetDigitValue(3, 16);	//N
					break;
				}
				else
				{
					display.SetDigitValue(0, 8);	//B
					display.SetDigitValue(1, 17);	//A
					display.SetDigitValue(2, 0);	//D
					display.SetDigitValue(3, 18);	//nothing
					
					long int delay = 0;
					
					while(1)
					{
						display.MultiplexDigits();
						
						_delay_ms(5);
						delay++;

						if(delay >= 200) //if about 1 second passed
						{
							display.SetAllDigitsToValue(13);
							digitPointer = 1;
							break;
						}
					}
					continue;
				}
			}

			display.SetDigitValue(digitPointer-1, static_cast<uint8_t>(pressedButton));
			digitPointer++;
		}

		if(digitPointer<6)
		{
			display.MultiplexDigits();
		}

		else
		{
			display.SetAllDigitsToValue('-');
			digitPointer = 1;
		}
	}
}