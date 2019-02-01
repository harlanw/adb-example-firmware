#ifndef _TS_CONFIG_H
#define _TS_CONFIG_H

#define BOARD_ID "ECE34xR1"

#ifndef F_CPU
	#warning "F_CPU not set... assumming 1MHz."
	#define F_CPU 1000000UL
#endif
#ifndef FTDI_BAUDRATE
	#warning "FTDI_BAUDRATE not set... assuming 9600bps"
	#define FTDI_BAUDRATE 9600UL
#endif

#endif
