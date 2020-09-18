#pragma once

#include <stdint.h>
#include "digit_value.h"

class Display
{
	/*Forward declaration*/
	enum class Position;
	
	public:
	Display();
	void SetAllDigitsToValue(DigitValue digitValue);
	void Clear();
	uint8_t GetDigitValue(uint8_t digit);
	void MultiplexDigits();
	void SetDigitValue(uint8_t position, DigitValue digitValue);
	
	private:
	enum class Position
	{
		POSITION_1 = 1,
		POSITION_2 = 2,
		POSITION_3 = 3,
		POSITION_4 = 4
	};
	
	void SetDigit(Position position, DigitValue digitValue);
	
	/*Table of values currently shown on 7-segment display*/
	DigitValue m_DigitValues[4];    
};