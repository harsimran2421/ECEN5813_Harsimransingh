include sources.mk

CC = cc
CFLAGS = -std=c99 -Wall -Werror -g -O0

SUBDIRS = additional

ifdef SUBDIRS
.PHONY : $(SUBDIRS)
$(SUBDIRS) : 
	@if [ -d $@ ]; then \
		$(MAKE) --no-print-directory --directory=$@ \
			CC=$(CC) CFLAGS="$(CFLAGS)" $(MAKECMDGOALS); \
	fi	
endif


THIRD_PARTY_DIR = additional
CMOCKA_INCLUDE_DIR = $(THIRD_PARTY_DIR)/build-Debug/include
CMOCKA_LIBRARY = $(THIRD_PARTY_DIR)/build-Debug/lib/libcmocka.a

cmocka : $(SUBDIRS)

CFLAGS += -I $(CMOCKA_INCLUDE_DIR)
CFLAGS += -I $(INCLUDE_H)
#
# quick and dirty build rules to demonstrate testing, not good build
# system practices.
#

#
# library
#
LIB_SRCS = \
	memory.c\
	conversion.c\
	circbuf.c

LIB_OBJS = $(LIB_SRCS:%.c=%.o)

LIB_HEADERS = $(LIB_SRCS:%.c=%.h)

LIB = libutils.a

#
# main executable
#
EXE_SRCS = main.c
EXE_OBJS = $(EXE_SRCS:%.c=%.o)

EXE = main.out

#
# tests
#
TEST_MEMORY_SRCS = \
	uinttest_memory.c

TEST_CONVERSION_SRCS = \
	unittest_data.c

TEST_BUFFER_SRCS = \
	unit_test_buffer.c

TEST_MEMORY_OBJS = $(TEST_MEMORY_SRCS:%.c=%.o)
TEST_CONVERSION_OBJS = $(TEST_COVERSION_SRCS:%.c=%.o)
TEST_BUFFER_OBJS = $(TEST_BUFFER_SRCS:%.c=%.o)

TEST_MEMORY_EXE = test-memory.out
TEST_CONVERSION_EXE = test-conversion.out
TEST_BUFFER_EXE = test-buffer.out


#
# Generic rule to generate objects
#
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB) : $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

all : $(LIB) $(EXE)

$(EXE) : $(EXE_OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ -lm

test_memory : $(TEST_MEMORY_EXE)
	./$(TEST_MEMORY_EXE)

test_conversion : $(TEST_CONVERSION_EXE)
	./$(TEST_CONVERSION_EXE)

test_buffer : $(TEST_BUFFER_EXE)
	./$(TEST_BUFFER_EXE)

$(TEST_MEMORY_EXE) : $(TEST_MEMORY_SRCS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(CMOCKA_LIBRARY) -lm

$(TEST_CONVERSION_EXE) : $(TEST_CONVERSION_SRCS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(CMOCKA_LIBRARY) -lm

$(TEST_BUFFER_EXE) : $(TEST_BUFFER_SRCS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(CMOCKA_LIBRARY) -lm

.PHONY : clean
clean :
	-rm -rf *~ *.o $(LIB) $(EXE) $(TEST_MEMORY_EXE) $(TEST_BUFFER_EXE) $(TEST_CONVERSION_EXE)  *.dSYM/

