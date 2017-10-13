/*
 * GccApplication1.c
 *
 * Created: 05/10/2017 12:15:57
 * Author : LMPC
 */ 

#include <avr/io.h>
//#define _NOP() do { __asm__ __volatile__ ("nop"); } while (0)

int main(void)
{
	
	DDRB |= (1<<PB0);
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB ^= (1<<PB0);
		 //_NOP();
    }
}

