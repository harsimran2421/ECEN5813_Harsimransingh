SRCS = main.c \
       project1.c \
       memory.c \
       conversion.c \
       debug.c \

LIBR = memory.c \
       conversion.c\

INCLUDE_H = ../includes/common/
INCLUDE_H_FF = ../includes/kl25z/
INCLUDE_H_FF1 = ../includes/CMSIS/
INCLUDE_LINKER = ../platform/MKL25Z128xxx4_flash.ld

vpath %.h $(INCLUDE_H)
