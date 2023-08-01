/*
 * CPPFile1.cpp
 *
 * Created: 05/03/2023 14:06:25
 *  Author: augus
 */ 
#include "Usart.h"
#include "EEPROM.h"
#include <avr/io.h>


void spi_master_init(void)
{
	DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2); // Set MOSI, SCK and SS as outputs
	DDRB &= ~(1 << DDB4); // Set MISO as input

	SPCR |= (1 << MSTR); // Set SPI mode as master
	SPCR |= (1 << SPR0) | (1 << SPR1);
	SPCR |= (1 << CPOL) | (1 << CPHA); // Set clock polarity and phase

	SPCR |= (1 << SPE); // Enable SPI
	PORTB &= ~(1 << PB2); //chip select et envoie 0
	SPDR = 0b00000000;
	while (!(SPSR & (1 << SPIF)));
	PORTB |= (1 << PB2);
	
	
}

void EEPROM_write(uint16_t address, uint8_t data)
{

	 PORTB &= ~(1 << PB2); // selection de l'esclave
	 SPDR = 0b00000110; // = 6  = WREN autorise à ecrire
	 
	 while (!(SPSR & (1 << SPIF)));
	 PORTB |= (1 << PB2);
	 PORTB &= ~(1 << PB2);
	 SPDR = 0b00000010;
	 
	 while (!(SPSR & (1 << SPIF)));
	 // Envoyer l'adresse de début d'écriture
	 SPDR = (uint8_t)(address >> 8);
	 
	 while (!(SPSR & (1 << SPIF)));
	 SPDR = (uint8_t)(address);
	 
	 while (!(SPSR & (1 << SPIF)));
	 // Envoyer les données à écrire
	 SPDR = data;
	 
	 while (!(SPSR & (1 << SPIF)));
	 PORTB |= (1 << PB2);
	 

	 //delay(500);
	 
	
	
}

uint8_t EEPROM_read(uint16_t address)
{
	uint8_t data;
	PORTB &= ~(1 << PB2); // SS = 0 ;

	// Envoyer l'instruction de lecture
	SPDR = 0b00000011;

	// Attendre que la transmission soit terminée
	while (!(SPSR & (1 << SPIF)));
	// Envoyer l'adresse de début de lecture
	SPDR = (uint8_t)(address >> 8);
	
	while (!(SPSR & (1 << SPIF)));
	SPDR = (uint8_t)(address);
	
	while (!(SPSR & (1 << SPIF)));
	// Lire les données depuis l'EEPROM
	SPDR = 0xFF; // Envoyer une valeur arbitraire pour déclencher la lecture
	
	while (!(SPSR & (1 << SPIF)));
	data = SPDR;

	PORTB |= (1 << PB2); // SS = 1 ;

	return data;
}