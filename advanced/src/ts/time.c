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

#include "time.h"

#include "attributes.h"

#include <stdio.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

static time_t runtime = { 0 };

static void
ts_time_tick(void);

ISR(TIMER1_COMPA_vect)
{
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		ts_time_tick();
	}
}

static void
ts_time_tick(void)
{
	++runtime.ms;

	if (runtime.ms == 1000)
	{
		++runtime.s;
		runtime.ms = 0;

		if (runtime.s == 60)
		{
			++runtime.m;
			runtime.s = 0;

			if (runtime.m == 60)
			{
				++runtime.h;
				runtime.m = 0;
			}
		}
	}
}

void
ts_time_init(void)
{
	TCCR1B |= _BV(WGM12) | _BV(CS00);
	OCR1A = 999;
	TIMSK1 |= _BV(OCIE1A);
}

time_t
hwclock(void)
{
	return runtime;
}
