#--------------------------------------------------------------------------------
##Author: Smitesh Modak, Harsimran Bindra
#Date Edited: 10/04/2017
#Description: makefile to build system which is independent of Platform
# 
#Targets:
#	<project.elf> - Builds <projec1.elf>
#	build - Build and links all source files
#	compile - Compiles all source files 
#	clean - remove the generated files
#
#-*-Makefile-*-
#target: Dependencies
#	action

include sources.mk

#Setting up of Default Platform
PLATFORM = HOST

#Common Compile Defines
PROG = project1
TARGET = $(PROG).elf

#Platform specific Compile Defines
ifeq ($(PLATFORM),HOST)
	CC = gcc
	LD = -ld
	CPPFLAGS += $(addprefix -I, $(INCLUDE_H))
	CFLAGS = -Wall -Werror -g -O0 -std=c99
	LDFLAGS = -Wl,-Map=$(PROG).map
endif

ifeq ($(PLATFORM),BBB)
	CC = arm-linux-gnueabihf-gcc
	LD = arm-linux-gnueabihf-ld
	CPPFLAGS += $(addprefix -I, $(INCLUDE_H))
	CFLAGS = -mcpu=cortex-a8 -Wall -Werror -g -O0 -std=c99 -mfloat-abi=hard -mfpu=neon -mthumb 
	LDFLAGS = -Wl,-Map=$(PROG).map
endif 

ifeq ($(PLATFORM),KL25Z)
	CC = arm-none-eabi-gcc
	LD = arm-none-eabi-ld
	CPPFLAGS += $(addprefix -I, $(INCLUDE_H) $(INCLUDE_H_FF) $(INCLUDE_H_FF1))
	CFLAGS = -mcpu=cortex-m0plus --specs=nosys.specs -Wall -Werror -g -o0 -std=c99 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=soft
	LDFLAGS =-Wl,-Map=$(PROG).map $(LINKF)
	LINKF += $(addprefix -T,$(INCLUDE_LINKER))
	SRC_O = $(SRC_K:c. =.o)
	SRC_D = $(SRC_K:c =.dep)
endif


OBJS = $(SRCS:.c=.o)
DEP = $(SRCS:.c=.dep)

#Build rules to directly compile
%.i : %.c
	$(CC) $(CFLAGS) -E $^ > $@

%.asm : %.c
	$(CC) $(CFLAGS) -S $^ > $@

%.o : %.c 
	$(CC) $(CPPFLAGS) -c -DPROJECT1 $^ $(CFLAGS) -o $@

%.dep : %.c
	$(CC) -M $(CPPFLAGS) $^ $(CFLAGS) > $@


.PHONY: all
build: all
all: $(TARGET) 

$(TARGET): $(OBJS) $(SRC_O) $(SRC_D) $(DEP)
	$(CC) $(OBJS) $(SRC_O) $(CFLAGS) -o $@ $(LDFLAGS)
	size -d $(TARGET)

#Compile time switch commands
compile-all: $(OBJS) $(SRC_O)
	$(CC) $(CPPFLAGS) $^ $(CFLAGS) $(LDFLAGS)

static-link: main.o libproject1
	$(CC) $(CPPFLAGS) -o $@ main.o libproject1

build-lib: memory.o conversion.o project1.o
	ar rcs libproject1.a $^

project1.exe: $(INCLUDE_LINKER) main.o project1.o conversion.o debug.o memory.o
	$(LD) $(CPPFLAGS) -Map=project1.map $(LINKF) -N -o main.o project1.o conversion.o debug.o memory.o

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET) $(DEP) $(PROG).map *.i *.s
	 
