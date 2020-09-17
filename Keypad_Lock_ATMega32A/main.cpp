#define F_CPU 1000000

#include <stdint.h>
#include <util/delay.h>	 //header containing delay functions
#include "functions.h"
#include "keypad.h"
#include "display.h"

void UserSetsCode(uint8_t * code);

void CompareEnteredCodeWithAdminCode(uint8_t * enteredCode, uint8_t * code);

Display display;
Keypad keypad;

int main(void)
{
	uint8_t code[4];											//table storing code set by admin
	uint8_t enteredCode[4];										//table storing code entered by user

	init_ports();
	
	UserSetsCode(code);
	
	display.SetAllDigitsToValue(13);										//set display to '-.' in locked state
	
	CompareEnteredCodeWithAdminCode(enteredCode, code);
	
	while(1)
	{
		display.MultiplexDigits();
	}
}

void UserSetsCode(uint8_t * code)
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

void CompareEnteredCodeWithAdminCode(uint8_t * enteredCode, uint8_t * code)
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