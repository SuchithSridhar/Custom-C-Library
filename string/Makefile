CC = gcc
CFLAGS = -O3
CSTD = c18
TARGET = string

.PHONEY = clean all test
# fPIC: Position Independent Code
# shared: make a shared library
SHARED_FLAGS = -fPIC -shared

BINS=test/lib_test lib$(TARGET).so
CURRENT_DIR = $(shell pwd)

all: lib$(TARGET).o lib$(TARGET).so

lib$(TARGET).so: $(TARGET).h lib$(TARGET).c
	$(CC) --std=$(CSTD) $(CFLAGS) $(SHARED_FLAGS) -o $@ lib$(TARGET).c

lib$(TARGET).o: $(TARGET).h lib$(TARGET).c
	$(CC) --std=$(CSTD) -c $(CFLAGS) -o $@ lib$(TARGET).c

# Compile for gdb
debug: lib$(TARGET).c ./test/testing.c
	$(CC) -o test/lib_test --std=$(CSTD) -g lib$(TARGET).c ./test/testing.c

test: test/lib_test
	./test/lib_test

test/lib_test: lib$(TARGET).o test/testing.c
	$(CC) -o $@ --std=$(CSTD) lib$(TARGET).o ./test/testing.c

clean:
	rm -f ./test/lib_test *.o *.so
