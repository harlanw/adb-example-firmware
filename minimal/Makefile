#
# Copyright (c) 2018-2019 Harlan Waldrop <harlan@ieee.org>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

NAME = minimal

CC  =  avr-gcc
CP  =  avr-objcopy

ISP_TOOL = usbtiny
ISP_TARGET = m644p

TARGET = atmega644pa
TARGET_ARCH = avr5

CFLAGS = -std=c11 -mmcu=$(TARGET)

default:
	$(CC) $(CFLAGS) -c -o main.o main.c
	$(CC) $(CFLAGS) -o $(NAME).elf main.o
	$(CP) -j .text -j .data -O ihex $(NAME).elf $(NAME).hex

flash:
	sudo avrdude -p $(ISP_TARGET) -c $(ISP_TOOL) -P usb -B 16 -U flash:w:$(NAME).hex -v

listen:
	stty -F /dev/ttyUSB0 -echo -onlcr
	cat -v < /dev/ttyUSB0

clean:
	rm -f main.o $(NAME).elf $(NAME).hex

.PHONY: clean default flash listen
