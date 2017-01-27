#include <avr/io.h>
#include <avr/interrupt.h>

#define BAUD 57600
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init(unsigned int);
volatile char ReceivedByte;

int main( void )
{

	int check=0x80;
	DDRC |= (1<<PC4)|(1<<PC5);
	DDRB |= (1<<PB2);
	USART_Init(MYUBRR);
	
	while(1)
	{

		check= ReceivedByte;
		if (check==0x36)
			PORTC|=(1<<PC5);
		else PORTC&=~(1<<PC5);
		if (check==0x11)
		{
			PORTC|=(1<<PC4);
		}
		else PORTC&=~(1<<PC4);
		if (check==0x80)
			PORTB|=(1<<PC2);
		else PORTB&=~(1<<PC2);
		sei();
		
	}
}

ISR(USART_RX_vect)
{
	ReceivedByte = UDR0; // Fetch the recieved byte value into the variable "ByteReceived"
	UDR0 = ReceivedByte; // Echo back the received byte back to the computer
	cli();

}

void USART_Init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit, non parity */
	UCSR0C =(3<<UCSZ00);

	UCSR0B |= (1 << RXCIE0);
	sei();
}

