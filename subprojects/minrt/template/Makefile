#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#

.SUFFIXES:

# Path to gba-minrt
MINRT		:= ..

# Name of your ROM
PROJECT		:= gba-minrt-template

# Source files
SOURCES		:= $(MINRT)/src/crt0.s src/main.c

# Include directories
INCLUDES	:= $(MINRT)/src

# Library directories, with /include and /lib
LIBDIRS		:= $(MINRT)

# Libraries to link
LIBS		:=

# All build output goes here
BUILDDIR	:= build

# Compiler flags (all languages)
ALLFLAGS	:=

# C compiler flags
CFLAGS		:= -g3 -gdwarf-4 -O2 -std=c99 -ffunction-sections -fdata-sections

# C++ compiler flags
CXXFLAGS	:=

# Assembler flags (as passed to GCC)
ASFLAGS		:=

# Linker flags (as passed to GCC)
LDFLAGS		:= -mthumb -specs=$(MINRT)/lib/nocrt0.specs \
		-specs=nano.specs -specs=nosys.specs \
		-Wl,-Trom.ld -Wl,--no-warn-rwx-segments

# Uncomment this if you want to use Link Time Optimization
#
# USE_LTO		:= yes

# Toolchain prefix
#
# Only change this if you want to use a different compiler
TOOLCHAIN	:= arm-none-eabi

#
# Internal Functions
#

# String equality
eq	= $(if $(and $(findstring x$(1),x$(2)),$(findstring x$(2),x$(1))),y,)

# Map relative directory names into build tree
pathmap	= $(1)$(subst $(subst ,, ),/,$(foreach component,$(subst /, ,$(2)),$(if $(call eq,$(component),..),__,$(component))))$(3)

# Object and dependency filename functions
obj	= $(call pathmap,$(BUILDDIR)/obj/,$(1),.o)
dep	= $(call pathmap,$(BUILDDIR)/dep/,$(1),.d)

# Language detection by filenames (taken from GCC docs)
is-c	= $(if $(filter %.c %.i %.h,$(1)),y,)
is-cxx	= $(if $(filter %.ii %.cc %.cp %.cxx %.cpp %.CPP %.c++ %.C \
	%.hh %.H %.hp %.hxx %.hpp %.HPP %.h++ %.tcc,$(1)),y,)
is-asm	= $(if $(filter %.s %.S %.sx,$(1)),y,)

# Language-specific compiler flag list generation
flags	= $(or \
	$(if $(call is-c,$(1)),$(CFLAGS),),\
	$(if $(call is-cxx,$(1)),$(CXXFLAGS),),\
	$(if $(call is-asm,$(1)),$(ASFLAGS),)) $(ALLFLAGS)

#
# Internal Variables
#

# Verbosity
SILENT	:= $(if $(VERBOSE),,@)

# Tools
CC 	:= $(TOOLCHAIN)-gcc
CXX	:= $(TOOLCHAIN)-g++
OBJCOPY	:= $(TOOLCHAIN)-objcopy
LD	:= $(if $(call is-cxx,$(SOURCES)),$(CXX),$(CC))
RUNNER	:= mgba-qt

# Primary build artifacts
ELFFILE	:= $(BUILDDIR)/$(PROJECT).elf
ROMFILE	:= $(BUILDDIR)/$(PROJECT).gba
MAPFILE	:= $(BUILDDIR)/$(PROJECT).map

# Default compiler flags
ALLFLAGS += \
	-mcpu=arm7tdmi \
	-mabi=aapcs \
	-mthumb \
	$(LIBDIRS:%=-I%/include) \
	$(INCLUDES:%=-I%) \
	$(if $(USE_LTO),-flto,-fno-lto) \

# Default linker flags
LDFLAGS	+= \
	-Wl,--gc-sections \
	-Wl,-Map,$(MAPFILE) \
	$(LIBDIRS:%=-L%/lib) \
	$(LIBS:%=-l%) \
	$(if $(USE_LTO),-flto,-fno-lto) \

# Build artifacts
OBJECTS	:= $(foreach source,$(SOURCES),$(call obj,$(source)))
DEPENDS	:= $(foreach source,$(SOURCES),$(call dep,$(source)))
DIRS	:= $(dir $(BUILDDIR) $(OBJECTS) $(DEPENDS))

#
# Targets
#

$(ROMFILE): $(ELFFILE)
$(ELFFILE): $(OBJECTS)
$(OBJECTS): | dirs

$(foreach source,$(SOURCES),$(eval $(call obj,$(source)): $(source)))

#
# Rules
#

%.o:
	@echo "compile $<"
	$(SILENT)$(CC) -c -o $@ $(call flags,$<) -MMD -MP -MF $(call dep,$<) $<

%.elf:
	@echo "link    $@"
	$(SILENT)$(LD) -o $@ $^ $(LDFLAGS)

%.gba:
	@echo "objcopy $@"
	$(SILENT)$(OBJCOPY) -O binary $< $@

dirs:
	@echo "mkdir   $(BUILDDIR)"
	$(SILENT)mkdir -p $(DIRS)

clean:
	@echo "clean $(BUILDDIR)"
	$(SILENT)rm -rf $(BUILDDIR)

run: $(ELFFILE)
	@echo "run $(ELFFILE)"
	$(SILENT)$(RUNNER) $<

.PHONY: dirs clean run

-include $(DEPENDS)
