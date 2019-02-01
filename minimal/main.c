/*
 * Copyright (c) 2018-2019 Harlan Waldrop <harlan@ieee.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <avr/io.h>

#define F_CPU 1000000UL
#define FTDI_BAUDRATE 9600UL

int usart_putchar(char c, FILE *stream);
int usart_getchar(FILE *stream);

FILE usart_out = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE usart_in  = FDEV_SETUP_STREAM(NULL, usart_getchar, _FDEV_SETUP_READ);

int
usart_putchar(char c, FILE *stream)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;

	return ((unsigned char) c);
}

int
usart_getchar(FILE *stream)
{
	loop_until_bit_is_set(UCSR0A, RXC0);

	return ((unsigned char) UDR0);
}

void
usart_init(void)
{
	#define BAUDSET ((F_CPU)/(8*(FTDI_BAUDRATE))-1)
	UCSR0A |= _BV(U2X0);

	UBRR0L = BAUDSET;
	UBRR0H = BAUDSET >> 8;

	#undef BAUDSET

	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);

	stdout = &usart_out;
	stdin = &usart_in;
}

int main(void)
{
	usart_init();

	printf("Hello, world!\n");

	for (;;);

	return 0;
}
