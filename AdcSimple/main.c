/*
 * AdcSimple.c
 *
 * Created: 10/10/2017 13:58:04
 * Author : LMPC
 */ 

/*
 * hbridgeBLDC4.c
 *
 * Created: 09/10/2017 18:31:49
 * Author : LMPC
 */ 



#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdlib.h>


#define PI 3.14159265

#define NoOfSections 6
#define countTo 50
#define AMPLITUDE 150

#define H1p PB1
#define L1p PB2

#define H2p PD5
#define L2p PD6

#define H3p PB3
#define L3p PD3

double H1=128;
double L1=0;
double H2=0;
double L2=128;
double H3=128;
double L3=0;
void setupADC();

volatile int Section=1;
volatile long int count=0;
unsigned  int dutycycle=0;
int main(void)
{
	
	DDRB |= (1 << H1p) | (1 << L1p) | (1 << H3p);
	DDRD |= (1 << H2p) | (1 << L2p) | (1 << L3p) | (1 << PD7);
	
	
	TCCR0A = (1 << COM0B1) | (1 << COM0A1) | (1 << WGM00) ;

	
	TIMSK0 = (1 << TOIE0);
setupADC();
	
	sei();
	
	TCCR0B |= (1 << CS00) ;

	
	while (1)
	{
		//cli();
		
ADCSRA  |= (1<<ADSC);	// Start conversion
while (ADCSRA &  (1<<ADSC));
// wait until conversion  completes; ADSC=0 means Complete

dutycycle = ADC/4;	//Store ADC result

		
	//	sei();
	}
}



ISR(TIMER0_OVF_vect)
{



	OCR0A = dutycycle;



}

void setupADC()
{
	
	ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2) ;
	ADCSRA = (1 << ADEN)| (1 << ADPS2) |  (1 << ADPS0);


}