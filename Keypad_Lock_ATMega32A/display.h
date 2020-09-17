#pragma once

#include <stdint.h>

class Display
{
	public:
	Display();
	void SetAllDigitsToValue(uint8_t value);
	void Clear();
	uint8_t GetDigitValue(uint8_t digit) {return m_DigitValues[digit];}
	void MultiplexDigits();
	void SetDigitValue(uint8_t position, uint8_t value);
	
	private:
	void SetDigit(uint8_t value, uint8_t position);
	
	uint8_t m_DigitValues[4] = {'-', '-', '-', '-'};          //table of values currently shown on 7-segment display
};