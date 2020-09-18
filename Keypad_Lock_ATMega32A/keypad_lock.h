#pragma once

#include "keypad.h"
#include "display.h"

class KeypadLock
{
	public:
	KeypadLock();
	void Execute();
	
	private:
	void InitPorts();
	void UserSetsCode();
	void CompareEnteredCodeWithAdminCode();
	
	Display m_Display;
	Keypad m_Keypad;
	uint8_t m_Password[4];											//table storing code set by admin
	
	enum class PasswordState
	{
		PasswordNotSet = 0,
		PasswordSet = 1
	} m_PasswordState;
};