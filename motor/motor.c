#include <avr/io.h>
#include <avr/interrupt.h>

volatile int x,y;
int main (void)
{
   DDRB |= (1 << PB2); // Set LED as output

   DDRB |= (1 << PB0);
   DDRD |= (1 << PD5)|(1 << PD6)|(1 << PD7);

   TIMSK1 |= (1 << TOIE1); // Enable overflow interrupt
   sei(); // Enable global interrupts

   TCCR1B |= (1 << CS11)|(1 << CS10); // Start timer at Fcpu/8

	x=2;
	y=1;

	volatile char D1=0;
	volatile char D2=1;
   for (;;)
   {

	if (x<=0) 
	{
		x=2;
		D1^=1;
	}
	if (y<=0) 
	{
		y=2;
		D2^=1;
	}
	
	if (D1)
	{
		PORTB |= (1 << PB0);
		PORTD &=~ (1 << PD7);
	}
	else
	{
		PORTB &= ~(1 << PB0);
		PORTD |= (1 << PD7);
	}

		if (D2)
	{
		PORTD |= (1 << PD5);
		PORTD &=~ (1 << PD6);
	}
	else
	{
		PORTD &= ~(1 << PD5);
		PORTD |= (1 << PD6);
	}


//	sei();
   }
}

ISR(TIMER1_OVF_vect)
{
	PORTB^= (1 << PB2);


 		 x--;
 		 y--;



 //  cli();
}
