/*
 * TimersSync.c
 *
 * Created: 15/06/2017 20:54:09
 * Author : LMPC
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{
	DDRB |= (1 << PB2); // Set LED as output
   TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
	DDRD |= (1 << PD5); // Set LED as output
	TIMSK0 |= (1 << TOIE0); // Enable overflow interrupt
	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt
	sei(); // Enable global interrupts
	OCR1A   = 32768; // Set CTC compare value to 
	TCCR1B |= (1 << CS11); // Start timer at Fcpu/8
	TCCR0B |= (1 << CS02) | (1 << CS00); // Start timer at Fcpu/1024

	for (;;)
	{

	}
}

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << PB2); // Toggle the LED
}

ISR(TIMER0_OVF_vect)
{
	PORTD ^= (1 << PD5); // Toggle the LED
}
