#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#

CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar

PROJECT = minrt

SOURCES = \
	src/gba/rom_header.s \
	src/gba/crt0.s \
	src/gba/ram.c \

INCLUDES = \
	src/gba \
	include

CFLAGS = \
	-Os \
	-g3 -gdwarf-4 \
	-ffunction-sections \
	-fdata-sections \
	-std=c99 \
	-Wall \
	-Wpedantic \
	-mabi=aapcs \
	-mcpu=arm7tdmi \
	-mthumb \
	$(INCLUDES:%=-I%) \
	$(INCLUDES:%=-Wa,-I%)

BUILD = build
LIB   = lib


#
# You don't need to touch anything below this point!
#

TARGET  = $(LIB)/lib$(PROJECT).a

OBJECTS = $(SOURCES:%=$(BUILD)/obj/%.o)
DEPENDS = $(SOURCES:%=$(BUILD)/dep/%.d)
OBJDIRS = $(dir $(OBJECTS) $(DEPENDS))

$(TARGET): $(OBJECTS)
	@echo "$@"
	@$(AR) rcs $@ $^

$(OBJECTS): | builddirs

$(BUILD)/obj/%.o: %
	@echo "$<"
	@$(CC) -c -o $@ $(CFLAGS) -MMD -MP -MF $(BUILD)/dep/$<.d $<

builddirs:
	@mkdir -p $(OBJDIRS) $(LIB)

clean:
	@echo "clean: $(BUILD) $(TARGET)"
	@rm -rf $(BUILD) $(TARGET)

install: $(TARGET)
	@echo "install: $(DESTDIR)$(DEVKITPRO)"
	@mkdir -p $(DESTDIR)$(DEVKITPRO)/libseven/
	@cp -r include $(DESTDIR)$(DEVKITPRO)/libseven/
	@cp -r lib $(DESTDIR)$(DEVKITPRO)/libseven/

.PHONY: builddirs clean install

-include $(DEPENDS)
