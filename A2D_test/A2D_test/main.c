#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

void setupADC();
void startConversion();

double dutyCycle=0;

int main(void)
{

	DDRD = (1 << PD6);
	
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK0 = (1 << TOIE0);
		
	setupADC();
	sei();
	
	TCCR0B =  (1 << CS00);
	while (1)
	{
		
	}
}

void setupADC()
{
	
		ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2) ;
		ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
		DIDR0 = (1 << ADC5D);
		
		startConversion();
}

void startConversion()
{
	ADCSRA |= (1 << ADSC);
	
}

ISR(ADC_vect)
{
	dutyCycle = ADC/4;
	startConversion();
}

ISR(TIMER0_OVF_vect)
{
	
	OCR0A = dutyCycle;
}