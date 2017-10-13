/*
 * hBridgeMicrostepping.c
 *
 * Created: 02/10/2017 17:39:31
 * Author : LMPC
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdlib.h>

//double count=0;
double A1=0;
double A2=0;
double B1=0;
double B2=0;

#define AMPLITUDE 255
#define countTo 100
#define PI 3.14159265

#define A1p PB1
#define A2p PB2
//#define portA PORTB

#define B1p PD5 
#define B2p PD6
//#define portB PORTD 

volatile int Step=1;
volatile long int count=0;
int main(void)
{
	
	   DDRB |= (1 << A1p) | (1 << A2p);
	   DDRD |= (1 << B1p) | (1 << B2p) | (1 << PD7);
	   
	   
	   TCCR0A = (1 << COM0B1) | (1 << COM0A1) | (1 << WGM00) ;
	   TCCR1A = (1 << COM1B1) | (1 << COM1A1) | (1 << WGM10) ;
	   //  TCCR0B = (1 << COM0B1) | (1 << WGM00) | (1 << WGM01);
	   TIMSK0 = (1 << TOIE0);
	   TIMSK1 = (1 << TOIE1);
	   
	   sei();
	   //TCCR0B = 0;
	   TCCR0B |= (1 << CS00) ;
	   TCCR1B |= (1 << CS10) ;
	   
	   double discreteTime = 0;
       
    while (1) 
    {
		cli();

		
		
		if (Step==1 || Step==2)
		//if (1)
		{
			A1=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)+(1.0/6.0))));
		}
		else if (Step==8)
		{
			A1=abs(AMPLITUDE*sin(2*PI*((discreteTime-7.0*countTo)/((6.0*countTo)/1.0))));
		}
		else
		{
			A1=0;
		}
		if (Step==2 || Step==3 || Step==4)
		//if (0)
		{
			B1=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)-(1.0/6.0))));
		}
		else
		{
			B1=0;
		}
		if (Step==4 || Step==5 || Step==6)
		//if (0)
		{
			A2=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)-(3.0/6.0))));
		}
		else
		{
			A2=0;
		}
		if (Step==6 || Step==7 || Step==8)
		//if (0)
		{
			B2=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)-(5.0/6.0))));
		}
		else
		{
			B2=0;
		}
		

		//A1=100*sin(2*3.14159*discreteTime/(8.0*countTo));
		
				if (count >= countTo-1)
				{
					PORTD &= ~(1 << PD7);
					if (Step>=8)
					{
						Step=0;
						discreteTime=0;
						PORTD |= (1 << PD7);
					}
					
					count=0;
					Step++;
				}
				discreteTime++;
				
		sei();
    }
}



ISR(TIMER0_OVF_vect)
{

	count++;

	OCR0A = (int) B2;
	OCR0B = (int) B1;

	OCR1A = (int) A1;
	OCR1B = (int) A2;


}

ISR(TIMER1_OVF_vect)
{
count++;

	OCR0A = (int) B2;
	OCR0B = (int) B1;

	OCR1A = (int) A1;
	OCR1B = (int) A2;

	//OCR1A = (B2/100)*255;
	//OCR1B = (A1/100)*255;

}