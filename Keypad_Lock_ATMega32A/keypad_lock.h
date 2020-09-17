#pragma once

#include "keypad.h"
#include "display.h"

class KeypadLock
{
	public:
	KeypadLock();
	
	private:
	void InitPorts(void);
	void UserSetsCode(uint8_t * code);
	void CompareEnteredCodeWithAdminCode(uint8_t * enteredCode, uint8_t * code);
	
	Display display;
	Keypad keypad;
	
	uint8_t password[4];											//table storing code set by admin
	uint8_t enteredPassword[4];										//table storing code entered by user
};