/*
 * IncFile1.h
 *
 * Created: 22/03/2023 13:53:28
 *  Author: augus
 */ 

// baudrate 19600

#ifndef Usart_H_
#define Usart_H_

void USART_Init();
unsigned char USART_Receive( void );
void USART_Transmit( unsigned char data );
void USART_Transmit_Trame( char chaine[], int nbr);



#endif /* INCFILE1_H_ */