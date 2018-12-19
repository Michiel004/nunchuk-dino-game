#ifndef RASP3SPI_H_
#define RASP3SPI_H_

#include "rasp3base.h"
#include <stdint.h>

#define SPI_BUFFER_SIZE 100

void RP3_SPI_init(uint64_t clock);
void RP3_SPI_transmit(char *t, int amount);
void RP3_SPI_receive(char *r, int amount);
void RP3_SPI_transcieve(char *t, char *r, int amount);

#endif