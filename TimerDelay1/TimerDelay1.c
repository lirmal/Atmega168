#include <avr/io.h>

int main (void)
{
   DDRB |= (1 << PB2); // Set LED as output

   TCCR1B |= (1 << CS12) | (1 << CS10); // Set up timer

   for (;;)
   {
      // Check timer value in if statement, true when count matches 1/20 of a second
      if (TCNT1 >= 100)
      {
         PORTB ^= (1 <<  PB2); // Toggle the LED

         TCNT1 = 0; // Reset timer value
      } 
   }
} 
