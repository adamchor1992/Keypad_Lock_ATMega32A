#pragma once

#include "button.h"

class Keypad
{
	public:
	Button GetPressedButton(void);										//find out which button was pressed and return the value
	
	private:
	static const int DELAY_BETWEEN_ROWS_POLLING = 200;
	static const int DELAY_AFTER_BUTTON_PRESS_DETECTED = 100;
};