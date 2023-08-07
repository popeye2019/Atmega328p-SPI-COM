/*
 * EEPROM.cpp
 *
 * Created: 05/03/2023 21:48:25
 * Author : augus
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include "Usart.h"
#include "EEPROM.h"
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>


 //commentaire coucou 

  char data = 0 ;
  char buffer[8];



void USART_tx_string(char *data)
{
	while((*data != '\0'))
	{
		while(!(UCSR0A & (1 << UDRE0)));
		UDR0 = *data;
		data++;
	}
}

int main(void)
{
	
	char lettre = 97 ;
	int cpt = 0 ;
	spi_master_init();
	USART_Init();
	
	//EEPROM_write(404,70);
	

// ecrire eeprom
     for (uint16_t i = 0; i < 26 ;  i++)
     {
		 
		
			EEPROM_write(i,lettre+cpt);
			cpt = cpt + 1;
			 _delay_ms(50);
	     
     }

     // Lire eprom
     for (uint16_t i = 0 ; i < 27; i++)
     {
		       
		       data = EEPROM_read(i);
		       
		    
		       USART_Transmit(data);
			   USART_Transmit('_');
			
     }
  
  
    while (1) 
    {
    }
}

