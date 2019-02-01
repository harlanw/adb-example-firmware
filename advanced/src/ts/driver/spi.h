#ifndef _TS_DRIVER_SPI_H
#define _TS_DRIVER_SPI_H

#include <stdint.h>

void
spi_init(void);

uint8_t
spi_transmit(uint8_t send);

#endif
