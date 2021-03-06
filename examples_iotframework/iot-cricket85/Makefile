##																			
## This program is free software; you can redistribute it and/or modify		
## it under the terms of the GNU General Public License as published by		
## the Free Software Foundation; either version 2 of the License, or			
## (at your option) any later version.										
##																			
## This program is distributed in the hope that it will be useful,			
## but WITHOUT ANY WARRANTY; without even the implied warranty of			
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				
## GNU General Public License for more details.								
##																			
## You should have received a copy of the GNU General Public License			
## along with this program; if not, write to the Free Software				
## Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA	
## 																			

PROGRAM = iot-cricket85
MCU = attiny85
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS += -Wall -g -Os -DTARGET_AVR -mmcu=$(MCU) -I../../iot-framework
LDFLAGS += -L ../../iot-framework -l clixxIO_AVR_$(MCU)
OBJS = $(PROGRAM).o

CFLAGS += -Wall -g -Os -mmcu=$(MCU) 

# Be silent per default, but 'make V=1' will show all compiler calls.
ifneq ($(V),1)
  Q := @
endif

# Avrdude mcu parameters are different than in avr-gcc, so translate
DUDEMCU = $(MCU)
ifeq ($(MCU),attiny85)
  DUDEMCU = t85
  MCUFUSES = -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
endif

ifeq ($(MCU),attiny13)
  DUDEMCU = t13
endif

all: $(PROGRAM).hex

$(PROGRAM).elf: $(PROGRAM).o
	@printf "  LD      $(subst $(shell pwd)/,,$(@))\n"
	$(Q)$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(PROGRAM).hex: $(PROGRAM).elf
	@printf "  OBJCOPY $(subst $(shell pwd)/,,$(@))\n"
	$(Q)$(OBJCOPY) -O ihex $< $@

%.o: %.cpp
	@printf "  CC      $(subst $(shell pwd)/,,$(@))\n"
	$(Q)$(CC) $(CFLAGS) -o $@ -c $<

deploy: $(PROGRAM).hex
	@printf "  FLASH   $(PROGRAM).hex\n"
	$(Q)avrdude -c avrispv2 -P usb -p $(DUDEMCU) -U flash:w:$(PROGRAM).hex

fuses:
	#(Q)avrdude -p $(DUDEMCU) -P usb -c avrispmkii $(MCUFUSES) 
    
clean:
	@printf "  CLEAN   $(subst $(shell pwd)/,,$(OBJS))\n"
	$(Q)rm -f $(OBJS)
	@printf "  CLEAN   $(PROGRAM).elf\n"
	$(Q)rm -f *.elf
	@printf "  CLEAN   $(PROGRAM).hex\n"
	$(Q)rm -f *.hex
