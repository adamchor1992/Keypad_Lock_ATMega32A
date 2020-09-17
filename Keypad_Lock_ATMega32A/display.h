#pragma once

#include <stdint.h>

class Display
{
	/*Forward declaration*/
	enum class Position;
	
	public:
	Display();
	void SetAllDigitsToValue(uint8_t value);
	void Clear();
	uint8_t GetDigitValue(uint8_t digit) {return m_DigitValues[digit];}
	void MultiplexDigits();
	void SetDigitValue(uint8_t position, uint8_t value);
	
	private:
	enum class Position
	{
		POSITION_1 = 1,
		POSITION_2 = 2,
		POSITION_3 = 3,
		POSITION_4 = 4
	};
	
	void SetDigit(Position position, uint8_t value);
	
	uint8_t m_DigitValues[4] = {'-', '-', '-', '-'};          //table of values currently shown on 7-segment display
};