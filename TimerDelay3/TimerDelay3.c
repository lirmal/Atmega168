#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{
   DDRB |= (1 << PB2); // Set LED as output

   TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode

   TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt

   sei(); //  Enable global interrupts

   OCR1A   = 15624; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64

   TCCR1B |= ((1 << CS10) | (1 << CS11)); // Start timer at Fcpu/64

   for (;;)
   {

   }
}


ISR(TIMER1_COMPA_vect)
{
   PORTB ^= (1 << PB2); // Toggle the LED
} 
