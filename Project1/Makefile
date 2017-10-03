#-*-Makefile-*-

#target: Dependencies
#	action

ifeq ($(PLATFORM),HOST)
	CC = gcc
	CFLAGS = -c
	LDFLAGS = $(CC) -o
	CPPFLAGS = -Wall -Werror -g - O0 -std=c99
	OBJS = main.o project1.o memory.o conversion.o debug.o 
	PROG = main
else
ifeq ($(PLATFROM,BBB)
	CC = arm-linux-gnueabhihf-gcc
	CFLAGS = -c
	LDFLAGS = $(CC) -o
	CPPFLAGS = -Wall -Werror -g - O0 -std=c99
	OBJS = main.o project1.o memory.o conversion.o debug.o
	PROG = main
else 
ifeq ($(PLATFORM),KL25Z)
	cc = arm-none-eabi-gcc
	CFLAGS = -c
	LDFLAGS = $(CC) -o
	CPPFLAGS = -Wall -Werror -g - O0 -std=c99 -mcpu=?? \
		   -mthumb -march=?? -mfloat-abi=?? \
		   -mfpu=fpv4-sp-d16 --specs=nosys.specs
	OBJS = main.o project1.o memory.o conversion.o debug.o
	PROG = main	
endif
endif
endif

all: $(PROG)

main: $(OBJS)
	$(LDFLAGS) $(PROG) $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -DPROJECT1

project1.o: project1.c
	$(CC) $(CFLAGS) project1.c

memory.o: memory.c
	$(CC) $(CFLAGS) memory.c

conversion.o: conversion.c
	$(CC) $(CFLAGS) conversion.c

debug.o: debug.c
	$(CC) $(CFLAGS) debug.c

clean:
	rm $(OBS)
