#ifndef singleStep
#define singleStep
#include <avr/io.h>

int singleFullStep( int Direction, int Step);
int singleHalfStep( int Direction, int Step);


int singleFullStep( int Direction, int Step)
{	
	if (Direction==1)
	{
		if (Step >= 4)
		{
			Step=1;
		}
		else
		{
			Step++;
		}
	
	}

	if (Direction==2)
	{
		if (Step <= 1)
		{
			Step=4;
		}
		else
		{
			Step--;
		}
	
	}


	if (Step==1)
	{

		PORTD = (1 << PD4);
		PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));
	}
	else if (Step==2)
	{

		PORTD = (1 << PD6);
		PORTD &= ~((1 << PD4) | (1 << PD5) | (1 << PD7));
	}
	else if (Step==3)
	{

		PORTD = (1 << PD5);
		PORTD &= ~((1 << PD4) | (1 << PD6) | (1 << PD7));
	}
	else if (Step==4)
	{

		PORTD = (1 << PD7);
		PORTD &= ~((1 << PD4) | (1 << PD5) | (1 << PD6));
	}
	else
	{
		PORTD = 0;
		Step=1;
	}
	 return Step;
}


int singleHalfStep( int Direction, int Step)
{
	if (Direction==1)
	{
		if (Step >= 8)
		{
			Step=1;
		}
		else
		{
			Step++;
		}
		
	}

	if (Direction==2)
	{
		if (Step <= 1)
		{
			Step=8;
		}
		else
		{
			Step--;
		}
		
	}


	if (Step==1)
	{

		PORTD |= (1 << PD4);
		PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));
	}
	else if (Step==2)
	{

		PORTD |= (1 << PD4) | (1 << PD6);
		PORTD &= ~((1 << PD5) | (1 << PD7));
	}
	else if (Step==3)
	{

		PORTD |= (1 << PD6);
		PORTD &= ~((1 << PD4) | (1 << PD5) | (1 << PD7));
	}
	else if (Step==4)
	{

		PORTD |= (1 << PD6) | (1 << PD5);
		PORTD &= ~((1 << PD4) | (1 << PD7) );
	}
	else if (Step==5)
	{
		PORTD |= (1 << PD5);
		PORTD &= ~((1 << PD4) | (1 << PD6) | (1 << PD7));
	}
	else if (Step==6)
	{
		PORTD |= (1 << PD5) | (1 << PD7);
		PORTD &= ~((1 << PD4) | (1 << PD6) );
	}
	else if (Step==7)
	{
		PORTD |= (1 << PD7);
		PORTD &= ~((1 << PD4) | (1 << PD5) | (1 << PD6));
	}
	else if (Step==8)
	{
		PORTD |= (1 << PD7) | (1 << PD4);
		PORTD &= ~((1 << PD5) | (1 << PD6));
	}
	else
	{
		PORTD = 0;
		Step=1;
	}
	return Step;
}

#endif