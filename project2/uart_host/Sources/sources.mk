#Defining common source files to be used
SRCS = main.c \
       project2.c\
       memory.c \
       conversion.c\
			 circbuf.c\
			 uart.c

#Defining source files to be used for KL25Z in addition to common source files
ifeq ($(PLATFORM),KL25Z)
	SRCS = main.c\
				 project2.c\
				 memory.c\
				 debug.c\
				 conversion.c\
				 system_MKL25Z4.c\
				 startup_MKL25Z4.s\
				 uart.c\
				 circbuf.c
endif

#Defining paths for the header files
INCLUDE_H = ../Includes/common/
INCLUDE_H_FF = ../Includes/KL25Z/
INCLUDE_H_FF1 = ../Includes/CMSIS/
INCLUDE_LINKER = ../platform/MKL25Z128xxx4_flash.ld

vpath %.h $(INCLUDE_H)
vpath %.h $(INCLUDE_H_FF)
vpath %.h $(INCLUDE_H_FF1) 
vpath %.h $(INLCUDE_H_FF1)

