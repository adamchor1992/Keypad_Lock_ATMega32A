#pragma once

#include <stdint.h>

class Display
{
	public:
	void SetDigit(uint8_t number, uint8_t position);
	void SetValueOnWholeDisplay(uint8_t value, uint8_t displayed_values[]);
	void Clear();
};