/*
 * DebouncingTest.c
 *
 * Created: 14/01/2017 12:15:09
 * Author : LMPC
 */ 

#define F_CPU 16000000UL
#define	numberOfButtons 1

#include <avr/io.h>
#include <avr/io.h>
#include <util/delay.h>
#include "ButtonDebounce.h"



int main(void)
{
	
	DDRD |= (1 << PD6) | (1 << PD5);
	DDRB &= ~(1 << PB0);
	PORTB &= ~(1 << PB0);
	int count=0;
	int pressed=0;
    while (1) 
    {/*
		if (PINB & (1<<PB0))
		{
			PORTD |= (1 << PD6);
			PORTD &= ~(1 << PD5);
		}
		else
		{
			PORTD |= (1 << PD5);
			PORTD &= ~(1 << PD6);
		}
		*/
	
		//if (PINB & (1<<PB0)) // switch is pressed
		if (ButtonPressed(0, PINB, 0, 30)) // switch is pressed - debounced
		{
			if (count >= 5)
			{
				PORTD ^= (1 << PD6);
				count=0;
			}
			pressed=1;
			
		}
		else //switch is not pressed
		{
			if (pressed)  // switch was pressed last time
			{
				count++;
				pressed=0; // pressed goes from 1 => 0
			}
		}
    }
}

