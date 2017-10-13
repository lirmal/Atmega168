/*
 * uartHbridge.c
 *
 * Created: 28/09/2017 19:47:12
 * Author : LMPC
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <util/delay.h>


#define BAUD 57600
#define MYUBRR F_CPU/16.0/BAUD-1
void USART_Init(unsigned int);
volatile char ReceivedByte;
volatile char MotorDirection;

double dutyCycle=0;

int main( void )
{

	//int check=0x80;
	DDRC |= (1<<PC4)|(1<<PC5);
	DDRB |= (1<<PB2);
	
		DDRD = (1 << PD6) | (1 << PD5);
		
		TCCR0A = (1 << COM0A1) | (1 << COM0B1) |  (1 << WGM00) ;
		TIMSK0 = (1 << TOIE0);
		
		OCR0A = (dutyCycle/100)*255;
		MotorDirection=0;
		ReceivedByte=0;
		
	USART_Init(round(MYUBRR));
	
	TCCR0B = (1 << CS01);
	
	while(1)
	{
		
		
		/*_delay_ms(100);
		dutyCycle += 10;
		
		if (dutyCycle > 100)
		{
			dutyCycle=0;
		} */
		dutyCycle = 0x7f & ReceivedByte;
		MotorDirection = ReceivedByte & 0x80;
		//dutyCycle =  ReceivedByte;
		/* check= ReceivedByte;
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
		else PORTB&=~(1<<PC2); */
		sei();
		
	}
}

ISR(USART_RX_vect)
{
	ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
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

ISR(TIMER0_OVF_vect)
{
	
	if (MotorDirection)
	{
		OCR0A = dutyCycle*0xff/0x7f;
		OCR0B=0;
	}
	else if (!MotorDirection)
	{
		OCR0A =0;
		OCR0B=dutyCycle*0xff/0x7f;
	}
}