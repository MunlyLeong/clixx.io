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

PROGRAM = lightsensor
MCU = linux
CC = g++
CFLAGS += -Wall -g
LDFLAGS += -lstdc++ 
LDLIBS += -L ../libraries -static -l clixxIO_Linux
OBJS = $(PROGRAM).o

# Be silent per default, but 'make V=1' will show all compiler calls.
ifneq ($(V),1)
Q := @
endif

all: $(OBJS)
	$(Q)$(CC) $(OBJS) -o $(PROGRAM) $(CLIXXLIBS) $(LDLIBS) 

%.o: %.cpp
	@printf "  CC      $(subst $(shell pwd)/,,$(@))\n"
	$(Q)$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	@printf "  CLEAN   $(subst $(shell pwd)/,,$(OBJS))\n"
	$(Q)rm -f $(OBJS)
	@printf "  CLEAN   $(PROGRAM).elf\n"
	$(Q)rm -f *.elf
	@printf "  CLEAN   $(PROGRAM).hex\n"
	$(Q)rm -f *.hex
