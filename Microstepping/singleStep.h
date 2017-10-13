#ifndef singleStep
#define singleStep
#include <avr/io.h>
#include <math.h>

int singleFullStep( int Direction, int Step ,double count);
int singleHalfStep( int Direction, int Step ,int count);


int singleFullStep( int Direction, int Step ,double count)
{	
	/*if (Direction==1)
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
	
	}*/
	
	if (count >= 1000)
	{

		count = 0;
	}
	else
	{
		count++;
	}
	/*
	if (count<=500)
	{

		A1=100*sin(2*3.14159*(count/1.0));
		A2=0;
		B1=0;
		B2=0;
	}
	else if (count>250 && count <=750)
	{

		A1=0;
		A2=0;
		B1=100*sin(2*3.14159*((count-250)/1.0));
		B2=0;
	}
	else if (count>500 && count <=1000)
	{

		A1=0;
		A2=100*sin(2*3.14159*((count-500)/1.0));
		B1=0;
		B2=0;
	}
	else if (count>750 && count <=250)
	{

		A1=0;
		A2=0;
		B1=0;
		B2=100*sin(2*3.14159*((count-750)/1.0));
	}
	else
	{
		A1=0;
		A2=0;
		B1=0;
		B2=0;
		Step=1;
	}
	*/
	A1=sin(count/10.0);
	

	 return Step;
}


int singleHalfStep( int Direction, int Step ,int count)
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

		A1=50;
		A2=0;
		B1=0;
		B2=0;
	}
	else if (Step==2)
	{

		A1=50;
		A2=0;
		B1=50;
		B2=0;
	}
	else if (Step==3)
	{

		A1=0;
		A2=0;
		B1=50;
		B2=0;
	}
	else if (Step==4)
	{
		A1=0;
		A2=50;
		B1=50;
		B2=0;

	}
	else if (Step==5)
	{
		A1=0;
		A2=50;
		B1=0;
		B2=0;
	}
	else if (Step==6)
	{
		A1=0;
		A2=50;
		B1=0;
		B2=50;
	}
	else if (Step==7)
	{
		A1=0;
		A2=0;
		B1=0;
		B2=50;
	}
	else if (Step==8)
	{
		A1=50;
		A2=0;
		B1=0;
		B2=50;
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