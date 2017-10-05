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
#---------------------------------------------------------------------------------

include sources.mk

#Setting up of Default Platform
PLATFORM = HOST
KL25ZFLAG = OFF
#Common Compile Defines
PROG = project1
TARGET = $(PROG).elf

#Platform specific Compile Defines
 
ifeq ($(PROJECT1-SW),ON)
	PROJECT1FLAG = PROJECT1
else
	PROJECT1FLAG = OFF
endif

ifeq ($(DEBUG),ON)
	DEBUGFLAG = VERBOSE
else
	DEBUGFLAG = OFF
endif

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
	LDFLAGS =-Wl,-Map=$(PROG).map 
	LINKF += $(addprefix -T, $(INCLUDE_LINKER))
	KL25ZFLAG = KL25Z
endif

OBJS = $(SRCS:.c=.o)
DEP = $(SRCS:.c=.dep)

#Build rules to directly compile:
#preproccessor files
%.i : %.c
	$(CC) $(CFLAGS) -E $^ > $@

#assembly file
%.asm : %.c
	$(CC) $(CFLAGS) -S $^ > $@

#object files
%.o : %.c 
	$(CC) $(CPPFLAGS) -c -D$(PROJECT1FLAG) -D$(DEBUGFLAG) -D$(KL25ZFLAG) $^ $(CFLAGS) -o $@

#dependency files
%.dep : %.c
	$(CC) -M $(CPPFLAGS) $^ $(CFLAGS) > $@

#This is used to tell make file that take the names listed as target and not consider them as files
.PHONY: all clean compile-all static-link build-lib direct-link build 

build: all

all: $(TARGET) 

#This is used to produce executable file
$(TARGET): $(OBJS) $(SRC_O) $(SRC_D) $(DEP)
	$(CC) $(CPPFLAGS) $(OBJS) $(SRC_O) $(CFLAGS) $(LINKF) -o $@ $(LDFLAGS)
	size -d $(TARGET)

#This is used to just compile files without linking 
compile-all: $(OBJS) $(SRC_O)
	$(CC) $(CPPFLAGS) $^ $(CFLAGS) $(LDFLAGS)

static-link: main.o libproject1.a
	$(CC) $(CPPFLAGS) -o $@ main.o libproject1.a

#This is to create archive static library
build-lib: memory.o conversion.o project1.o
	ar rcs libproject1.a $^

#This is used to invoke linker without gcc
project1: $(OBJS)
	$(LD) $(CPPFLAGS) startup_MKL25Z4.s -o main.o project1.o memory.o conversion.o debug.o system_MKL25Z4.o $(LINKF) -N --entry main
#This is used to create executeable without invoking gcc for host
direct-link: $(OBJS) 
	ld $(CPPFLAGS) -o direct-linkk.elf $^ -lc -N --entry main

#This is used to remove object,dependency,executable,map,preprocessor,.s and .exe files
clean:
	rm -f $(OBJS) $(DEP) $(TARGET) $(PROG).map $(SRC_O) $(SRC_D) *.i *.s *.exe
	 
