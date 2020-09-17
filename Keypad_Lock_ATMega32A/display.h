#pragma once

#include <stdint.h>

class Display
{
	public:
	Display();
	
	void SetAllDigitsToValue(uint8_t value);
	void Clear();
	uint8_t GetDigitValue(uint8_t digit) {return digitsOnDisplay[digit];}
	void MultiplexDigits();
	void SetDigitValue(uint8_t position, uint8_t value);
	
	private:
	void SetDigit(uint8_t value, uint8_t position);
	
	uint8_t digitsOnDisplay[4] = {'-', '-', '-', '-'};          //table of values currently shown on 7-segment display
};