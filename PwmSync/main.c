/*
 * PwmSync.c
 *
 * Created: 17/06/2017 12:20:33
 * Author : LMPC
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

int main (void)
{
	DDRB |= (1 << PB2); // Set LED as output
	DDRD |= (1 << PD5); // Set LED as output
	
	TCCR1A |= (1 <<  WGM10) | (1 <<  COM1B1);
	TIMSK1 |= (1 << TOIE1); // Enable CTC interrupt
	
	TCCR0A |= (1 <<  WGM00) | (1 <<  COM0B1);
	TIMSK0 |= (1 << TOIE0); // Enable overflow interrupt
	
	sei(); // Enable global interrupts
	OCR1B   = 120; // Set CTC compare value to 
	OCR0B   = 120; // Set CTC compare value to 
	TCCR1B |= (1 << CS11); // Start timer at Fcpu/8
	TCCR0B |= (1 << CS01); // Start timer at Fcpu/8

	for (;;)
	{

	}
}

ISR(TIMER1_OVF_vect)
{
	PORTB ^= (1 << PB2); // Toggle the LED
}

ISR(TIMER0_OVF_vect)
{
	PORTD ^= (1 << PD5); // Toggle the LED
}
