CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m0plus --specs=nosys.specs -Wall -g -o0 -std=c99 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=soft
LDFLAGS =-Wl,-Map=main.map
target:
		$(CC) HW5.c $(CFLAGS) -TMKL25Z128xxx4_flash.ld -o main.elf $(LDFLAGS)
