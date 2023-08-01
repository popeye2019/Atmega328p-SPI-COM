/*
 * EEPROM.h
 *
 * Created: 05/03/2023 14:03:11
 *  Author: augus
 */ 
// Adresse de l'eeporm sur 16bits
// taille des données sur 8bits

#include <avr/io.h>
#include "Usart.h"



#define EEPROM_SIZE 20  // Taille de l'EEPROM AT25512 en octets

#ifndef EEPROM_H_
#define EEPROM_H_


void spi_master_init(void);
void EEPROM_write(uint16_t address, uint8_t data);
uint8_t EEPROM_read(uint16_t address);


#endif /* INCFILE1_H_ */