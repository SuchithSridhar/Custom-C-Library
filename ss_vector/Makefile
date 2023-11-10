CC = gcc
CFLAGS = -O3
CSTD = c18
TARGET = ssvector
LIB_DIR = suchilib

# fPIC: Position Independent Code
# shared: make a shared library
SHARED_FLAGS = -fPIC -shared

BINS=test/lib_test lib$(TARGET).so
CURRENT_DIR = $(shell pwd)

.PHONEY = clean all test debug

all: lib$(TARGET).o lib$(TARGET).so

lib$(TARGET).o: $(TARGET).h lib$(TARGET).c
	$(CC) --std=$(CSTD) -c $(CFLAGS) -o $@ lib$(TARGET).c

lib$(TARGET).so: $(TARGET).h lib$(TARGET).c
	$(CC) --std=$(CSTD) $(CFLAGS) $(SHARED_FLAGS) -o $@ lib$(TARGET).c

test: test/lib_test test/test.sh
	bash test/test.sh

# Compile for gdb
debug: lib$(TARGET).c ./test/testing.c
	$(CC) -o test/lib_test --std=$(CSTD) -g lib$(TARGET).c ./test/testing.c

test/lib_test: lib$(TARGET).o test/testing.c
	$(CC) -o $@ --std=$(CSTD) lib$(TARGET).o ./test/testing.c

install: lib$(TARGET).so
	sudo mkdir -p /usr/lib/$(LIB_DIR)
	sudo mkdir -p /usr/include/$(LIB_DIR)

	sudo cp lib$(TARGET).so /usr/lib/$(LIB_DIR)
	sudo cp $(TARGET).h /usr/include/$(LIB_DIR)

clean:
	rm -f ./test/lib_test ./test/data/test*.out *.o *.so
