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

NAME = example

DEVICE=/dev/ttyUSB0

BUILD_PATH = ./build
OPTIMIZATION = -O3

CC = avr-gcc
CP = avr-objcopy
DP = avr-objdump

ISP = avrdude
ISP_TOOL = usbtiny
ISP_TARGET = m644p

TARGET = atmega644pa
TARGET_ARCH = avr5

F_CPU = 1000000UL

CDEFS_LIST = DEBUG F_CPU=$(F_CPU) USART_MODE=1
CDEFS = $(addprefix -D, $(CDEFS_LIST))

CFLAGS  = -std=c11 -Wall -Wno-unused -I./src
CFLAGS += -mmcu=$(TARGET)
CFLAGS += -g $(OPTIMIZATION) $(CDEFS)

SRC  = main.c
SRC += ts/ts.c
SRC += ts/time.c
SRC += ts/driver/spi.c ts/driver/usart.c
SRC_PATH = ./src

OBJ = $(addsuffix .o, $(SRC))
OBJ_PATH = $(addprefix $(BUILD_PATH)/, $(OBJ))

DEPS = $(OBJ_PATH:%.o=%.d)

BLD = \e[1m
RST = \e[0m

ELF = $(BUILD_PATH)/$(NAME).elf
HEX = $(BUILD_PATH)/$(NAME).hex

default: $(HEX)

flash: $(HEX)
	sudo $(ISP) -p $(ISP_TARGET) -c $(ISP_TOOL) -P usb -B 16 -U flash:w:$(HEX) -v

$(HEX): $(ELF)
	$(CP) -j .text -j .data -O ihex $^ $@

$(ELF): $(OBJ_PATH)
	@printf "$(BLD)CC$(RST)\t%s %s\n" $@ $<
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

-include $(DEPS)
$(BUILD_PATH)/%.c.o: $(SRC_PATH)/%.c
	@printf "$(BLD)MKDIR$(RST)"
	@printf "\t%s\n" $(@D)
	@mkdir -p $(@D)

	@printf "$(BLD)CC$(RST)\t%s %s\n" $@ $<
	@$(CC) $(CFLAGS) -MMD -c -o $@ $<

-include $(DEPS)
$(BUILD_PATH)/%.S.o: $(SRC_PATH)/%.S
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -c -o $@ $<

clean:
	@rm -rf $(BIN) $(DEPS) $(OBJ_PATH)
	@printf "$(BLD)RM$(RST)"
	@printf "\t%s %s\n" $(BIN) $(DEPS) $(OBJ_PATH)

docs:
	doxygen ./docs/Doxyfile

dump: $(ELF)
	$(DP) -m $(TARGET_ARCH) -S $^ > $^.dump
	@echo "Dumping $^ $(TARGET):$(TARGET_ARCH)"

sim: $(ELF)
	simavr -f $(F_CPU) -m atmega644 $(ELF)

listen:
	stty -F $(DEVICE) -echo -onlcr
	cat -v < $(DEVICE)

.PHONY: clean debug default docs dump flash listen sim
