/*
 * StepperSingleFullStep.c
 *
 * Created: 15/04/2017 14:17:13
 * Author : LMPC
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "singleStep.h"

volatile int count=0;

int main(void)
{
	volatile int Step=0;
	volatile int Direction=1; // 1-right, 2-left
	
	
	   DDRB &= ~(1 << PB0);
	   DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
	   
	   
	   TIMSK0 = (1 << TOIE0);
	   
	   sei();
	   //TCCR0B = 0;
	   TCCR0B = (1 << CS02) | (1<< CS00);

    while (1) 
    {
		if (count == 10)
		{
			if (PINB & (1<<PB0))
			{
				Step = singleFullStep(Direction,Step);
			}
			else
			{
				Step = singleHalfStep(Direction,Step);
			}
		//Step = singleFullStep(Direction,Step);
		//Step = singleHalfStep(Direction,Step);
		count = 0;
		}
		sei();
    }

}

ISR(TIMER0_OVF_vect)
{


	//Step++;
	/*if (PINB & (1<<PB0))
	{
		count++;
	}*/
	count++;
	cli();
}