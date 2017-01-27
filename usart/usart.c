#include <avr/io.h>


#define BAUD 38400
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init(unsigned int);
void USART_Transmit(unsigned char);
unsigned char USART_Receive( void );

int main( void )
{

	int check=80;
	DDRC |= (1<<PC4)|(1<<PC5);
	USART_Init(MYUBRR);
	
	while(1)
	{
	
		check=USART_Receive();	
		USART_Transmit(check);
		
		if (check==0x36)
			PORTC^=(1<<PC5);
		else PORTC&=~(1<<PC5);
		if (check==0x11)
		{
			PORTC^=(1<<PC4);
		}
		else PORTC&=~(1<<PC4);
		
	}
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
}

void USART_Transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
		;
	/* Put data into buffer, sends the data */
	UDR0= data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );

	/* Get and return received data from buffer */
	return UDR0;
}

