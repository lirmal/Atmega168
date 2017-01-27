#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

double dutyCycle=0;

int main(void)
{

	DDRD = (1 << PD6);
	
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK0 = (1 << TOIE0);
	
	OCR0A = (dutyCycle/100)*255;
	
	sei();
	
	TCCR0B =  (1 << CS00) | (1 << CS02);
    while (1) 
    {
		_delay_ms(100);
		dutyCycle += 10;
		
		if (dutyCycle > 100)
		{
			dutyCycle=0;
		}
		
    }
}

ISR(TIMER0_OVF_vect)
{
	
	OCR0A = (dutyCycle/100)*255;
}