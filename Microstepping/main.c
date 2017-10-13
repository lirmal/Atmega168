/*
 * Microstepping.c
 *
 * Created: 17/04/2017 10:20:42
 * Author : LMPC
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <util/delay.h>


double count=0;
double A1=0;
double A2=0;
double B1=0;
double B2=0;
#include "singleStep.h"

int main(void)
{
	volatile int Step=0;
	volatile int Direction=1; // 1-right, 2-left
	volatile int Tstep=0;
	
	
	   DDRB &= ~(1 << PB0);
	   DDRB |= (1 << PB1) | (1 << PB2);
	   DDRD |= (1 << PD5) | (1 << PD6);
	   
	   TCCR0A = (1 << COM0B1) | (1 << COM0A1) | (1 << WGM00) ;
	   TCCR1A = (1 << COM1B1) | (1 << COM1A1) | (1 << WGM10) ;
	 //  TCCR0B = (1 << COM0B1) | (1 << WGM00) | (1 << WGM01);
	   TIMSK0 = (1 << TOIE0);
	   TIMSK1 = (1 << TOIE1);
	   
	   sei();
	   //TCCR0B = 0;
	   TCCR0B |= (1 << CS00) ;
	   TCCR1B |= (1 << CS11) ;

    while (1) 
    {
		cli();
		
		//	if (PINB & (1<<PB0))
			//{
				if (Tstep==10000)
				{
					//Step = singleFullStep(Direction,Step,count);
					Tstep=0;
					_delay_ms(200);
				}
				else
				{
					Tstep++;
					A1=100*sin(Tstep/0.1);
					_delay_ms(200);
				}
				
			//}
			//else
			//{
				//Step = singleHalfStep(Direction,Step,count);
			//}
		//Step = singleFullStep(Direction,Step);
		//Step = singleHalfStep(Direction,Step);

		sei();
    }

}

ISR(TIMER0_OVF_vect)
{


	//Step++;
	/*if (PINB & (1<<PB0))
	{
		count++;
	}*/
	//count++;
	OCR0A = (A1/100)*255;
	OCR0B = (A1/100)*255;
	//OCR1A = (B1/50)*255;
	//OCR1B = (B2/50)*255;

	//cli();
}

ISR(TIMER1_OVF_vect)
{

	//count++;
	//OCR0A = (dutyCycle/50)*255;
	//OCR0B = (dutyCycle/50)*255;
	OCR1A = (A1/100)*255;
	OCR1B = (A1/100)*255;
	//cli();
}