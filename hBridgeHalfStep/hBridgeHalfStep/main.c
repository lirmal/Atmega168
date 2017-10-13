/*
 * hBridgeHalfStep.c
 *
 * Created: 02/10/2017 17:20:08
 * Author : LMPC
 */ 



#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define A1 PB1
#define A2 PB2
#define portA PORTB

#define B1 PD5 
#define B2 PD6
#define portB PORTD

volatile int Step=1;
volatile int count=0;
int main(void)
{
	
	   DDRB |= (1 << A1) | (1 << A2);
	   DDRD |= (1 << B1) | (1 << B2);
	   
	   
	   TIMSK0 = (1 << TOIE0);
	   
	   sei();
	   //TCCR0B = 0;
	   TCCR0B = (1 << CS01) | (1 << CS00) ;

    while (1) 
    {
		if (count == 154)
		{
			if (Step==1)
			{
				portA |= (1 << A1);
				portA &= ~(1 << A2);
				portB &= ~((1 << B1) | (1 << B2) );
			}
			if (Step==2)
			{
				portA |= (1 << A1);
				portB |= (1 << B1);
				portA &= ~(1 << A2);
				portB &= ~(1 << B2);
			}
			if (Step==3)
			{
				portB |=  (1 << B1);
				portB &= ~(1 << B2);
				portA &= ~((1 << A1) | (1 << A2) );

			}
			if (Step==4)
			{
				portB |=  (1 << B1);
				portA |=  (1 << A2);
				portB &= ~(1 << B2);
				portA &= ~(1 << A1) ;
			}
			if (Step==5)
			{
				portA |= (1 << A2);
				portA &= ~(1 << A1);
				portB &= ~((1 << B1) | (1 << B2) );
			}
			if (Step==6)
			{
				portB |=  (1 << B2);
				portA |=  (1 << A2);
				portB &= ~(1 << B1);
				portA &= ~(1 << A1) ;
			}
			if (Step==7)
			{
				portB |= (1 << B2);
				portB &= ~(1 << B1);
				portA &= ~((1 << A1) | (1 << A2) );
				Step=0;
			if (Step==6)
			{
				portB |=  (1 << B2);
				portA |=  (1 << A1);
				portB &= ~(1 << B1);
				portA &= ~(1 << A2) ;
			}
			}
			
			count=0;
			Step++;
		}
		
		sei();
    }
}

ISR(TIMER0_OVF_vect)
{


	//Step++;
	count++;
	cli();
}