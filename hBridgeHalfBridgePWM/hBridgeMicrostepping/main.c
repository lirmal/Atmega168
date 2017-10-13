/*
 * hBridgeMicrostepping.c
 *
 * Created: 02/10/2017 17:39:31
 * Author : LMPC
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

//double count=0;
double A1=0;
double A2=0;
double B1=0;
double B2=0;

#define dutyCycle 65

#define A1p PB1
#define A2p PB2
//#define portA PORTB

#define B1p PD5 
#define B2p PD6
//#define portB PORTD 

volatile int Step=1;
volatile int count=0;
int main(void)
{
	
	   DDRB |= (1 << A1p) | (1 << A2p);
	   DDRD |= (1 << B1p) | (1 << B2p);
	   
	   
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
		if (count >= 250)
		{
			if (Step==1)
			{
				A1=dutyCycle;
				A2=0;
				B1=0;
				B2=0;
			}
			else if (Step==2)
			{
				A1=dutyCycle;
				A2=0;
				B1=dutyCycle;
				B2=0;
			}
			else if (Step==3)
			{
				A1=0;
				A2=0;
				B1=dutyCycle;
				B2=0;

			}
			else if (Step==4)
			{
				A1=0;
				A2=dutyCycle;
				B1=dutyCycle;
				B2=0;
			}
			else if (Step==5)
			{
				A1=0;
				A2=dutyCycle;
				B1=0;
				B2=0;
			}
			else if (Step==6)
			{
				A1=0;
				A2=dutyCycle;
				B1=0;
				B2=dutyCycle;
			}
			else if (Step==7)
			{
				A1=0;
				A2=0;
				B1=0;
				B2=dutyCycle;
			}
			else if (Step==8)
			{
				A1=dutyCycle;
				A2=0;
				B1=0;
				B2=dutyCycle;
				Step=0;
			}
			else
			{
				A1=87;
				A2=87;
				B1=87;
				B2=87;
				Step=0;
			}
			
			
			count=0;
			Step++;
		}
		
		sei();
    }
}



ISR(TIMER0_OVF_vect)
{

	count++;

	OCR0A = (B2/100)*255;
	OCR0B = (B1/100)*255;

OCR1A = (A1/100)*255;
OCR1B = (A2/100)*255;
}

ISR(TIMER1_OVF_vect)
{


	//OCR1A = (B2/100)*255;
	//OCR1B = (A1/100)*255;

}