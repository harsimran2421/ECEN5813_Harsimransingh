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

#Common Compile Defines
PROG = project1
TARGET = $(PROG).elf

<<<<<<< HEAD
#Platform specific Compile Defines
=======
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

>>>>>>> Bug fixes
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
	SRC_O = $(SRC_K:.c =.o)
	SRC_D = $(SRC_K:.c =.dep)
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

<<<<<<< HEAD
#object files
%.o : %.c 
	$(CC) $(CPPFLAGS) -c -DPROJECT1 $^ $(CFLAGS) -o $@

#dependency files
%.dep : %.c
	$(CC) -M $(CPPFLAGS) $^ $(CFLAGS) > $@


.PHONY: all
=======
%.o : %.c 
	$(CC) $(CPPFLAGS) -c -D$(PROJECT1FLAG) -D$(DEBUGFLAG) $^ $(CFLAGS) -o $@
%.dep : %.c
	$(CC) -M $(CPPFLAGS) $^ $(CFLAGS) > $@
.PHONY: all clean compile-all static-link build-lib direct-link build 
>>>>>>> Bug fixes
build: all
all: $(TARGET) 

#This is used to produce executable file
$(TARGET): $(OBJS) $(SRC_O) $(SRC_D) $(DEP)
	$(CC) $(CPPFLAGS) $(OBJS) $(SRC_O) $(CFLAGS) $(LINKF) -o $@ $(LDFLAGS)
	size -d $(TARGET)

<<<<<<< HEAD
#This is used to just compile files without linking
compile-all: $(OBJS) $(SRC_O)
	$(CC) $(CPPFLAGS) $^ $(CFLAGS) $(LDFLAGS)
=======
compile-all: $(OBJS) 
	$(CC) $(CPPFLAGS) $^ $(CFLAGS)

static-link: main.o libproject1.a
	$(CC) $(CPPFLAGS) -o $@ main.o libproject1.a
>>>>>>> Bug fixes

#This is to create archive static library
build-lib: memory.o conversion.o project1.o
	ar rcs libproject1.a $^

<<<<<<< HEAD
#This is to use the static library created
static-link: main.o libproject1.a
	$(CC) $(CPPFLAGS) -o $@ main.o libproject1.a

#This is used to invoke linker without gcc
project1.exe: $(OBJS) $(SRC_O) $(LINKF) $(SRC_DEP)
	$(LD) $(CPPFLAGS) $(OBJS) $(SRC_O) -Map=project1.map $(LINKF) -o $@ 

.PHONY: clean
=======
direct-link: $(OBJS)
	ld $(CPPFLAGS) -o direct-linkk.elf $^ -lc -A -b -g --entry main
>>>>>>> Bug fixes

#This is used to remove object,dependency,executable,map,preprocessor,.s and .exe files
clean:
	rm -f $(OBJS) $(TARGET) $(DEP) $(PROG).map $(SRC_O) $(SRC_D) *.i *.s *.exe
	 
