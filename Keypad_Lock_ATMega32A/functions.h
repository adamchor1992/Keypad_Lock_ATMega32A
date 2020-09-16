#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void init_ports(void);												//initialize all ports for proper operation
void reset_ports(void);											//clear all ports
void set_display(uint8_t, uint8_t);								//set certain character to be displayed on one certain position on 7-segment display
void set_value_on_whole_display(uint8_t, uint8_t[]);				//set certain character to be displayed on all positions of 7-segment display
void clear_display(void);											//turn off all 7-segment display segments
uint8_t select_number(void);										//find out which button was pressed and return the value

#endif