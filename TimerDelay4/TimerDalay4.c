#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{
   DDRB |= (1 << PB2); // Set LED as output

   TIMSK1 |= (1 << TOIE1); // Enable overflow interrupt
   sei(); // Enable global interrupts

   TCCR1B |= (1 << CS11); // Start timer at Fcpu/8

   for (;;)
   {

   }
}

ISR(TIMER1_OVF_vect)
{
   PORTB ^= (1 << PB2); // Toggle the LED
} 
