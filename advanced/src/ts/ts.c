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

#include "attributes.h"
#include "config.h"
#include "time.h"
#include "driver/usart.h"

#include <avr/interrupt.h>
#include <avr/boot.h>

extern void user_init(void);
extern void user_main(void);

static void
check_board_id(void)
{
	char board_id[8];

	/*
	 * The board id is an 8 byte value stored in the beginning of eeprom.
	 * The eeprom on unprogrammed chips defaults to 0xFF.
	 *
	 * XXX: Won't persist through chip erase without EESAVE fusebit set:
	 *      -U hfuse:w:0x91:m
	 */
	eeprom_read_block((void *) &board_id, (const void *) 0, 8);

	if (board_id[0] == (char) 0xFF)
	{
		const char new_id[] = BOARD_ID;

		printf("Detected factory board... configuring as %s\n", new_id);
		eeprom_write_block((const void *) new_id, (void *) 0, 8);
		eeprom_read_block((void *) &board_id, (const void *) 0, 8);
	}
	printf("board_id: %.8s\n", board_id);

	/*
	 * Device signatures:
	 *   1E 96 0A = Atmega644p
	 */
	uint8_t sr[3];
	sr[0] = boot_signature_byte_get(0x0000);
	sr[1] = boot_signature_byte_get(0x0002);
	sr[2] = boot_signature_byte_get(0x0004);
	printf("signature: %02X %02X %02X\n", sr[0], sr[1], sr[2]);
}

static void ATTR_CTOR
ts_init(void)
{
	usart_init();

	stdout = &usart_out;
	stdin = &usart_in;

	check_board_id();
}

static void ATTR_DTOR
ts_end(void)
{
	/* Prevent device from restarting */
	for (;;);
}

int main(void)
{
	user_init();
	ts_time_init();
	sei();
	user_main();

	return 0;
}
