/*
 * StepperHalfStep.c
 *
 * Created: 28/01/2017 13:56:36
 * Author : LMPC
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int Step=1;
volatile int count=0;
int main(void)
{
	
	//   DDRB |= (1 << PB0);
	   DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
	   
	   
	   TIMSK0 = (1 << TOIE0);
	   
	   sei();
	   //TCCR0B = 0;
	   TCCR0B = (1 << CS01) ;

    while (1) 
    {
		if (count == 180)
		{
			if (Step==1)
			{
				PORTD |= (1 << PD4);
				PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));
			}
			if (Step==2)
			{
				PORTD |= (1 << PD4) | (1 << PD6);
				PORTD &= ~((1 << PD5) | (1 << PD7));
			}
			if (Step==3)
			{
				PORTD |= (1 << PD6);
				PORTD &= ~((1 << PD4) | (1 << PD5) | (1 << PD7));	
			}
			if (Step==4)
			{
				PORTD |= (1 << PD6) | (1 << PD5);
				PORTD &= ~((1 << PD4) | (1 << PD7) );

			}
			if (Step==5)
			{
				PORTD |= (1 << PD5);
				PORTD &= ~((1 << PD4) | (1 << PD6) | (1 << PD7));
			}
			if (Step==6)
			{
				PORTD |= (1 << PD5) | (1 << PD7);
				PORTD &= ~((1 << PD4) | (1 << PD6) );
			}
			if (Step==7)
			{
				PORTD |= (1 << PD7);
				PORTD &= ~((1 << PD4) | (1 << PD5) | (1 << PD6));
			}
			if (Step==8)
			{
				PORTD |= (1 << PD7) | (1 << PD4);
				PORTD &= ~((1 << PD5) | (1 << PD6));
				Step=0;
			}
			count=0;
			Step++;
		}
		
		sei();
    }
}

ISR(TIMER0_OVF_vect)
{


	//Step++;
	count++;
	cli();
}