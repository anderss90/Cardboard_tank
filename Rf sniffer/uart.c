/*
 * uart.c
 *
 * Created: 07.05.2014 20:38:14
 *  Author: Anders
 */ 

#include "common_variables.h"
#define USART_BAUDRATE		19200
#define BAUD_PRESCALE		(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
void uart_init(){
	UCSR0B	= (1 << RXEN0)  | (1 << TXEN0);		// turn on the transmission and reception circuitry
	UCSR0C	= (1 << UCSZ00) | (1 << UCSZ01);	// use 8-bit character sizes

	UBRR0H	= (BAUD_PRESCALE >> 8);				// upper 8-bits of baud rate value into high byte of UBRR register
	UBRR0L	= BAUD_PRESCALE;					// lower 8-bits of baud rate value into low byte of UBRR register

}

int uart_putchar(char c)
{
	while ((UCSR0A & (1 << UDRE0)) == 0)
	{
		// Do nothing until UDR is ready for more data to be written to it
	};

	UDR0 = c;									// transmit character

	return (0);									// transmit success
}