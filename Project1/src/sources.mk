SRCS = main.c \
       project1.c \
       memory.c \
       conversion.c \
       debug.c \

INCLUDE_H = ../includes/common/
INCLUDE_H_FF = ../includes/kl25z/
INCLUDE_H_FF1 = ../includes/CMSIS/
vpath %.h $(INCLUDE_H)
