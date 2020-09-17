#pragma once

#include "button.h"

void init_ports(void);												//initialize all ports for proper operation
void SetDigit(uint8_t, uint8_t);								//set certain character to be displayed on one certain position on 7-segment display
void SetValueOnWholeDisplay(uint8_t, uint8_t[]);				//set certain character to be displayed on all positions of 7-segment display