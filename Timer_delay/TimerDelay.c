
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRC|=(1<<PC4|1<<PC5);//D0 & D1 are outputs
	

	while(1)
	{
		PORTC^=(1<<PC4|1<<PC5); // blink
		_delay_ms(500);
	}

}
