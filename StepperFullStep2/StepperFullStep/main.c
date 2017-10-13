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
	
	   DDRB |= (1 << PB1) | (1 << PB2);
	   DDRD |= (1 << PD5) | (1 << PD6);
	   
	   
	   TIMSK0 = (1 << TOIE0);
	   
	   sei();
	   //TCCR0B = 0;
	   TCCR0B = (1 << CS01) | (1 << CS00) ;

    while (1) 
    {
		if (count == 254)
		{
			if (Step==1)
			{
				PORTB |= (1 << PB1);
				PORTB &= ~(1 << PB2);
				PORTD &= ~((1 << PD5) | (1 << PD6) );
			}
			if (0)
			{
				PORTB |= (1 << PB1) | (1 << PB2);
				PORTD &= ~((1 << PD5) | (1 << PD6));
			}
			if (Step==2)
			{
				PORTB |= (1 << PB2);
				PORTB &= ~(1 << PB1);
				PORTD &= ~((1 << PD5) | (1 << PD6) );
			}
			if (0)
			{
				PORTB |= (1 << PB2);
				PORTD |=  (1 << PD5);
				PORTB &= ~(1 << PB1);
				PORTD &= ~(1 << PD6);

			}
			if (Step==3)
			{
				PORTD |=  (1 << PD5);
				PORTD &= ~(1 << PD6);
				PORTB &= ~((1 << PB1) | (1 << PB2) );
			}
			if (0)
			{
				PORTD |= (1 << PD5) | (1 << PD6);
				PORTB &= ~((1 << PB1) | (1 << PB2) );
			}
			if (Step==4)
			{
				PORTD |= (1 << PD6);
				PORTD &= ~(1 << PD5);
				PORTB &= ~((1 << PB1) | (1 << PB2) );
				Step=0;
			}
			if (0)
			{
				PORTD |= (1 << PD6);
				PORTB |= (1 << PB1);
				PORTB &= ~(1 << PB2);
				PORTD &= ~(1 << PD5);
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