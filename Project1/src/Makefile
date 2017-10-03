#-*-Makefile-*-

#target: Dependencies
#	action

include sources.mk
PROG = project1
TARGET = $(PROG).elf
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
	CFLAGS = -mcpu=cortex-a8 -Wall -Werror -g -O0 -std=c99
	LDFLAGS = -Wl,-Map=$(PROG).map
endif 

ifeq ($(PLATFORM),KL25Z)
	CC = arm-none-eabi-gcc
	LD = arm-none-eabi-ld
	CPPFLAGS += $(addprefix -I, $(INCLUDE_H) $(INCLUDE_H_FF) $(INCLUDE_H_FF1))
	CFLAGS = -mcpu=cortex-m0plus --specs=nosys.specs -Wall -Werror -g -o0 -std=c99 -mthumb
	LDFLAGS =	-Wl,-Map=$(PROG).map	
endif

OBJS = $(SRCS:.c=.o)
DEP = $(SRCS:.c=.dep)

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

$(TARGET): $(OBJS) $(DEP)
	$(CC) $(OBJS) $(CFLAGS) -o $@ $(LDFLAGS)
	size -d $(TARGET)

compile-all: $(OBJS) 
	$(CC) $(CPPFLAGS) $^ $(CFLAGS)

static-link: main.o libproject1.a
	$(CC) $(CPPFLAGS) -o $@ main.o libproject1.a

build-lib: memory.o conversion.o project1.o
	ar rcs libproject1.a $^
.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET) $(DEP) $(PROG).map *.i *.s
	 
