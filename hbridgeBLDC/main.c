/*
 * hbridgeBLDC.c
 *
 * Created: 06/10/2017 10:20:59
 * Author : LMPC
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdlib.h>


#define PI 3.14159265

#define NoOfSections 6
#define countTo 20
#define AMPLITUDE 200

#define H1p PB1
#define L1p PB2

#define H2p PD5
#define L2p PD6

#define H3p PB3
#define L3p PD3

double H1=0;
double L1=0;
double H2=0;
double L2=0;
double H3=0;
double L3=0;

volatile int Section=1;
volatile long int count=0;
int main(void)
{
	
	DDRB |= (1 << H1p) | (1 << L1p) | (1 << H3p);
	DDRD |= (1 << H2p) | (1 << L2p) | (1 << L3p) | (1 << PD7);
	
	
	TCCR0A = (1 << COM0B1) | (1 << COM0A1) | (1 << WGM00) ;
	TCCR1A = (1 << COM1B1) | (1 << COM1A1) | (1 << WGM10) ;
	TCCR2A = (1 << COM2B1) | (1 << COM2A1) | (1 << WGM20) ;
		
	TIMSK0 = (1 << TOIE0);
	TIMSK1 = (1 << TOIE1);
	TIMSK2 = (1 << TOIE2);
	
	sei();
	
	TCCR0B |= (1 << CS00) ;
	TCCR1B |= (1 << CS10) ;
	TCCR2B |= (1 << CS20) ;
	
	double discreteTime = 0;
	
	while (1)
	{
		cli();

		switch (Section)
		{
			case 1:
			H1=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0))));
			L1=0;
			H2=0;
			L2=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)-(2.0/6.0))));
			H3=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)+(2.0/6.0))));
			L3=0;
			break;
			
			case 2:
			H1=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0))));
			L1=0;
			H2=0;
			L2=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)-(2.0/6.0))));
			H3=0;
			L3=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)+(2.0/6.0))));
			break;
			
			case 3:
			H1=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0))));
			L1=0;
			H2=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)-(2.0/6.0))));
			L2=0;
			H3=0;
			L3=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)+(2.0/6.0))));
			break;		
			
			case 4:
			H1=0;
			L1=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0))));
			H2=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)-(2.0/6.0))));
			L2=0;
			H3=0;
			L3=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)+(2.0/6.0))));
			break;	
			
			case 5:
			H1=0;
			L1=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0))));
			H2=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)-(2.0/6.0))));
			L2=0;
			H3=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)+(2.0/6.0))));
			L3=0;
			break;			
			
			case 6:
			H1=0;
			L1=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0))));
			H2=0;
			L2=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)-(2.0/6.0))));
			H3=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)+(2.0/6.0))));
			L3=0;
			break;						
		}
		
		

		//	B2=abs(AMPLITUDE*sin(2*PI*(discreteTime/((6.0*countTo)/1.0)-(5.0/6.0))));
	
		

		
		
		if (count >= countTo-1)
		{
			PORTD &= ~(1 << PD7);
			if (Section>=NoOfSections)
			{
				Section=0;
				discreteTime=0;
				PORTD |= (1 << PD7);
			}
			
			count=0;
			Section++;
		}
		discreteTime++;
		
		sei();
	}
}



ISR(TIMER0_OVF_vect)
{

	count++;

	OCR0A = (int) H1;
	OCR0B = (int) L1;

	OCR1A = (int) H2;
	OCR1B = (int) L2;
	
	OCR2A = (int) H3;
	OCR2B = (int) L3;	


}

ISR(TIMER1_OVF_vect)
{
	count++;

	OCR0A = (int) H1;
	OCR0B = (int) L1;

	OCR1A = (int) H2;
	OCR1B = (int) L2;
	
	OCR2A = (int) H3;
	OCR2B = (int) L3;

}

ISR(TIMER2_OVF_vect)
{
	count++;

	OCR0A = (int) H1;
	OCR0B = (int) L1;

	OCR1A = (int) H2;
	OCR1B = (int) L2;
	
	OCR2A = (int) H3;
	OCR2B = (int) L3;

}