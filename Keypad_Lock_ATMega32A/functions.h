#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "button.h"

void init_ports(void);												//initialize all ports for proper operation
void setDigit(uint8_t, uint8_t);								//set certain character to be displayed on one certain position on 7-segment display
void setValueOnWholeDisplay(uint8_t, uint8_t[]);				//set certain character to be displayed on all positions of 7-segment display
void clear_display(void);											//turn off all 7-segment display segments
Button GetPressedKey(void);										//find out which button was pressed and return the value

#endif