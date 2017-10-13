#ifndef singleStep
#define singleStep
#include <avr/io.h>

int singleFullStep( int Direction, int Step);
int singleHalfStep( int Direction, int Step);


int singleFullStep( int Direction, int Step)
{	
	int Amp=50;
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

		A1=Amp;
		A2=0;
		B1=0;
		B2=0;
	}
	else if (Step==2)
	{

		A1=0;
		A2=0;
		B1=Amp;
		B2=0;
	}
	else if (Step==3)
	{

		A1=0;
		A2=Amp;
		B1=0;
		B2=0;
	}
	else if (Step==4)
	{

		A1=0;
		A2=0;
		B1=0;
		B2=Amp;
	}
	else
	{
		A1=0;
		A2=0;
		B1=0;
		B2=0;
		Step=1;
	}

	 return Step;
}


int singleHalfStep( int Direction, int Step)
{
	int Amp=50;
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

		A1=Amp;
		A2=0;
		B1=0;
		B2=0;
	}
	else if (Step==2)
	{

		A1=Amp;
		A2=0;
		B1=Amp;
		B2=0;
	}
	else if (Step==3)
	{

		A1=0;
		A2=0;
		B1=Amp;
		B2=0;
	}
	else if (Step==4)
	{
		A1=0;
		A2=Amp;
		B1=Amp;
		B2=0;

	}
	else if (Step==5)
	{
		A1=0;
		A2=Amp;
		B1=0;
		B2=0;
	}
	else if (Step==6)
	{
		A1=0;
		A2=Amp;
		B1=0;
		B2=Amp;
	}
	else if (Step==7)
	{
		A1=0;
		A2=0;
		B1=0;
		B2=Amp;
	}
	else if (Step==8)
	{
		A1=Amp;
		A2=0;
		B1=0;
		B2=Amp;
	}
	else
	{
		A1=0;
		A2=0;
		B1=0;
		B2=0;
		Step=1;
	}
	return Step;
}

#endif