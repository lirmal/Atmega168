#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{
   DDRB |= (1 << PB2); // Set LED as output

   DDRD |= (1 << PD5); // Set LED as output
   TIMSK0 |= (1 << TOIE0); // Enable overflow interrupt
   TIMSK1 |= (1 << TOIE1); // Enable overflow interrupt
   sei(); // Enable global interrupts

   TCCR1B |= (1 << CS11); // Start timer at Fcpu/8
   TCCR0B |= (1 << CS02) | (1 << CS00); // Start timer at Fcpu/8

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
