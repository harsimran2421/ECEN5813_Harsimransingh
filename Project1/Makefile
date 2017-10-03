#-*-Makefile-*-

#target: Dependencies
#	action

include sources.mk

ifeq ($(PLATFORM),HOST)
	CC = gcc
	LD = -ld
	PROG = project1
	TARGET = $(PROG).elf
	CFLAGS = -Wall -Werror
	LDFLAGS = -Wl,-Map=$(PROG).map
endif

ifeq ($(PLATFROM),BBB)
	CC = arm-linux-gnueabhihf-gcc
	LD = arm-linux-gnueabhihf-ld
	PROG = project1
	TARGET = $(PROG).elf
	CFLAGS = -Wall -Werror -g -O0 -std=c99
	LDFLAGS = -Wl,-Map=$(PROG).map
endif 

ifeq ($(PLATFORM),KL25Z)
	CC = arm-linux-gnueabhihf-gcc
        LD = arm-linux-gnueabhihf-ld
        PROG = project1
        TARGET = $(PROG).elf
        CFLAGS = -Wall -Werror -g -O0 -std=c99
        LDFLAGS = -Wl,-Map=$(PROG).map	
endif

OBJS = $(SRCS:.c=.o)

%.o : %.c 
	$(CC) -c -DPROJECT1 $< $(CFLAGS) -o $@

.PHONY: all
build: all
.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).map 
	 
