#define F_CPU 1000000	

#include <stdint.h>
#include <util/delay.h>	 //header containing delay functions
#include "functions.h"

int main(void)
{
	uint8_t i=1;													//iterator
	uint8_t number_on_keypad=0;										//value read from keypad
	uint8_t number_to_show[4]={'-','-','-','-'};                    //table of values currently shown on 7-segment display
	uint8_t code[4];												//table storing code set by admin
	uint8_t entered_code[4];										//table storing code entered by user

	init_ports();

    while (1) 
	{
		number_on_keypad = select_number();							//poll for value on keypad

		if(number_on_keypad!=200)									//if input changed
		{
			if(number_on_keypad==12)								//if cancel button was pressed
			{
				set_value_on_whole_display('-', number_to_show);
				i=1;
				continue;
			}
			
			if(i==5 && number_on_keypad==11)						//if 4 digits were entered and OK button was pressed
			{
				code[0]=number_to_show[0];
				code[1]=number_to_show[1];
				code[2]=number_to_show[2];
				code[3]=number_to_show[3];
				break;
			}
			
			number_to_show[i-1]=number_on_keypad;
			i++;
		}

		if(i<6)
		{
			set_display(number_to_show[0],1);
			set_display(number_to_show[1],2);
			set_display(number_to_show[2],3);
			set_display(number_to_show[3],4);
		}

		else
		{
			set_value_on_whole_display('-', number_to_show);
			i=1;
		}
	}
	
	set_value_on_whole_display(13, number_to_show);										//set display to '-.' in locked state

	
	i=1;															//reset iterator
	
	long int del=0;

	//COMPARING ENTERED CODE WITH CODE SET BEFORE
	while (1)
	{
		number_on_keypad = select_number();							//poll for value on keypad

		if(number_on_keypad!=200)									//if input changed
		{
			if(number_on_keypad==12)								//if cancel button was pressed
			{
				set_value_on_whole_display(13, number_to_show);
				i=1;
				continue;
			}
			
			if(i==5 && number_on_keypad==11)						//if 4 digits were entered and OK button was pressed
			{
				entered_code[0]=number_to_show[0];
				entered_code[1]=number_to_show[1];
				entered_code[2]=number_to_show[2];
				entered_code[3]=number_to_show[3];
				
				if(entered_code[0]==code[0] && entered_code[1]==code[1] && entered_code[2]==code[2] && entered_code[3]==code[3]) //check if code is correct
				{
					number_to_show[0]=0; //O
					number_to_show[1]=14;//P
					number_to_show[2]=15;//E
					number_to_show[3]=16;//N
					break;
				}
				
				else
				{
					number_to_show[0]=8;   //B
					number_to_show[1]=17;  //A
					number_to_show[2]=0;   //D
					number_to_show[3]=18;  //nothing
					
					while(1)
					{
						set_display(number_to_show[0],1);
						set_display(number_to_show[1],2);
						set_display(number_to_show[2],3);
						set_display(number_to_show[3],4);
						
						_delay_ms(5);
						del++;

						if(del>=200) //if about 1 second passed
						{
							del=0;	 //reset delay cycles counter
							set_value_on_whole_display(13, number_to_show);
							i=1;	 //reset iterator
							break;
						}
					}
					continue;
				}
			}	
			number_to_show[i-1]=number_on_keypad;
			i++;
		}

		if(i<6)
		{
			set_display(number_to_show[0],1);
			set_display(number_to_show[1],2);
			set_display(number_to_show[2],3);
			set_display(number_to_show[3],4);
		}

		else
		{
			set_value_on_whole_display('-', number_to_show);
			i=1;
		}
	}
	
	while(1)
	{
		set_display(number_to_show[0],1);
		set_display(number_to_show[1],2);
		set_display(number_to_show[2],3);
		set_display(number_to_show[3],4);
	}
}