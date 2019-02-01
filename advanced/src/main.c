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

#include "ts/time.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#ifdef DEBUG
	#define DPRINT(fmt, ...)                     \
	{                                            \
		time_t t = hwclock();                    \
		printf("[%02u:%02u:%02u.%03u] %s: " fmt, \
			t.h, t.m, t.s, t.ms,                 \
			__PRETTY_FUNCTION__, ##__VA_ARGS__); \
	}
#else
	#define DPRINT(fmt, ...) ((void) 0)
#endif

void
user_init(void)
{
	DPRINT("initializing firmware\r\n");

	/* DEMO LED GPIO */
	DDRA = 0xE0;
	PORTA = 0xE0; /* led is common anode so 1 turns led off */
}

void
user_main(void)
{
	bool running = true;
	while (running)
	{
		char buffer[256];
		char *read = fgets(buffer, sizeof(buffer), stdin);
		if (read)
		{
			DPRINT("pong %s", read);

			if (strcmp(read, "r\r\n") == 0)
				PORTA = 0xDF;
			else if (strcmp(read, "g\r\n") == 0)
				PORTA = 0x7F;
			else if (strcmp(read, "b\r\n") == 0)
				PORTA = 0xBF;
			else
				PORTA = 0x00;
		}

		_delay_ms(250);
		PORTA = 0xFF;
	}
}
