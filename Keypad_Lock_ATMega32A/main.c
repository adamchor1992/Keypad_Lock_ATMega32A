/*
 * Keypad_Lock_ATMega32A.c
 *
 * Created: 2017-12-08 14:50:43
 * Author : Adam
 */ 
#define F_CPU 1000000												//1MHz
#include <avr/io.h>
#include <util/delay.h>												//header containing delay functions

 void init_ports(void);												//initialize all ports for proper operation
 void reset_ports(void);											//clear all ports
 void set_display(uint8_t, uint8_t);								//set certain character to be displayed on one certain position on 7-segment display
 void set_value_on_whole_display(uint8_t, uint8_t[]);				//set certain character to be displayed on all positions of 7-segment display
 void clear_display(void);											//turn off all 7-segment display segments
 uint8_t select_number(void);										//find out which button was pressed and return the value

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

 void init_ports(void)
 {
 	reset_ports();
 	clear_display();

 	
 	DDRA = 255;									//output_port_A driving 7 segment display
 	DDRB |= (1<<0) | (1<<1) | (1<<2) | (1<<3);  //PORT0, PORT1, PORT2, PORT3 driving 7 segment display

 	DDRD |= (1<<0)|(1<<1)|(1<<2)|(1<<3);		//PIN0,PIN1,PIN2,PIN3 set as output, rest as input
 	
 	PORTD=255;									//set whole PORT to 1 (INVERSE LOGIC)
 	
 	PORTD |= (1<<4)|(1<<5)|(1<<6)|(1<<7);		//pull-up on input PINS of PORTD
 }

void reset_ports(void)
{
	DDRA=0;
	DDRB=0;
	DDRC=0;
	DDRD=0;
	PORTA=0;
	PORTB=0;
	PORTC=0;
	PORTD=0;
}

void set_display(uint8_t number, uint8_t position)
{
	switch(position)
	{
		case 1:
		PORTB &= ~(1<<0);
		break;

		case 2:
		PORTB &= ~(1<<1);
		break;

		case 3:
		PORTB &= ~(1<<2);
		break;

		case 4:
		PORTB &= ~(1<<3);
		break;
	}

	switch(number)
	{
		case 0:
		PORTA=~(0x3F);
		break;

		case 1:
		PORTA=~(0x06);
		break;

		case 2:
		PORTA=~(0x5B);
		break;

		case 3:
		PORTA=~(0x4F);
		break;

		case 4:
		PORTA=~(0x66);
		break;

		case 5:
		PORTA=~(0x6D);
		break;

		case 6:
		PORTA=~(0x7D);
		break;
		
		case 7:
		PORTA=~(0x07);
		break;

		case 8:
		PORTA=~(0x7F);
		break;

		case 9:
		PORTA=~(0x6F);
		break;
		
		case '-':      // display '-'
		PORTA=~(0x40);
		break;
		
		case '.':	   // display '.'
		PORTA=~(0x80);
		break;
		
		case 13:
		PORTA=~(0xC0); // display '-' and '.' simultaneously
		break;
		
		case 14:
		PORTA=~(0x73); // letter P
		break;
		
		case 15:
		PORTA=~(0x79); // letter E
		break;
		
		case 16:
		PORTA=~(0x37); // letter N
		break;
		
		case 17:
		PORTA=~(0x77);  //  letter A
		break;
		
		case 18:
		PORTA=~(0x0);  //display nothing
		break;
	}
	_delay_us(600);
	clear_display();
}

void set_value_on_whole_display(uint8_t value, uint8_t displayed_values[])
{
	int i=0;
	for(i=0; i<4;i++)
	{
		*(displayed_values + i) = value;
	}
}

void clear_display(void)
{
	PORTA=255;
	PORTB=255;
}

uint8_t select_number(void)
{
			uint8_t column_value;
			
			// FIRST ROW

			_delay_us(200);
			PORTD &= ~(1<<0); // 0 on first row;
			_delay_us(200);

			column_value = PIND;

			if(!(column_value & 1<<4))
			{
				//1
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 1;
			}
			else if(!(column_value & 1<<5))
			{
				//2
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 2;
			}
			else if(!(column_value & 1<<6))
			{
				//3
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 3;
			}
			else if(!(column_value & 1<<7))
			{
				//4
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 4;
			}

			PORTD |= (1<<0); // 1 on first row;
			
			_delay_us(200);

			// SECOND ROW

			PORTD &= ~(1<<1); // 0 on second row;
			_delay_us(200);

			column_value = PIND;

			if(!(column_value & 1<<4))
			{
				//5
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 5;
			}
			else if(!(column_value & 1<<5))
			{
				//6
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 6;
			}
			else if(!(column_value & 1<<6))
			{
				//7
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 7;
			}
			else if(!(column_value & 1<<7))
			{
				//8
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 8;
			}

			PORTD |= (1<<1); // 1 on second row;

			_delay_us(200);

			// THIRD ROW
			
			PORTD &= ~(1<<2); // 0 on third row;
			_delay_us(200);

			column_value = PIND;

			if(!(column_value & 1<<4))
			{
				//9
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 9;
			}
			else if(!(column_value & 1<<5))
			{
				//0
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 0;
			}
			else if(!(column_value & 1<<6))
			{
				//OK
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 11;
			}
			else if(!(column_value & 1<<7))
			{
				//CANCEL
				while(1)
				{
					if(PIND!=column_value)
					break;
				}
				_delay_ms(100);
				return 12;
			}

			PORTD |= (1<<2); // 0 on third row;

			_delay_us(200);

			return 200;      //reserved value meaning that input did not change
}
