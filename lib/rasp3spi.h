#ifndef RASP3SPI_H_
#define RASP3SPI_H_

#include "rasp3base.h"
#include <stdint.h>

#define SPI_BUFFER_SIZE 100

/**Initialize the spi port. 
   The clock will be shifted if needed.*/
void RP3_SPI_init(uint64_t clock);

/**Transmit the given chars.*/
void RP3_SPI_transmit(char *t, int amount);

/**Receive the requested chars.*/
void RP3_SPI_receive(char *r, int amount);

/**Transmit the given chars and receive the same amount.*/
void RP3_SPI_transcieve(char *t, char *r, int amount);

#endif