/*
 * CPPFile1.cpp
 *
 * Created: 22/03/2023 13:55:58
 *  Author: augus
 */ 
#include "Usart.h"
#include <avr/io.h>


void USART_Init(  )
{
	/* Set the baud rate */ 
	UBRR0 = 51;
	
	/* RAZ du registre de controle A	*/
	UCSR0A = 0x00 ;

	/* Enable USART receiver, transmitter and interrupRX*/
	UCSR0B = ( ( 1 << RXEN0 ) | ( 1 << TXEN0 ) | (1<<RXCIE0));
	
	/* Set frame format: 8 data 2stop */
	UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
	
}

/****************On crée une fonction pour recevoir****************/
unsigned char USART_Receive( void )
{
	
	while ( !(UCSR0A & (1<<RXC0)) );
	
	return UDR0;
}

/****************On crée une fonction pour transmettre des caracteres****************/
void USART_Transmit( unsigned char data )
{
	
	while ( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;

}