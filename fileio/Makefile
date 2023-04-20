CC = gcc
CFLAGS = -O3
CSTD = c18
TARGET = fileio

# fPIC: Position Independent Code
# shared: make a shared library
SHARED_FLAGS = -fPIC -shared

BINS=test/lib_test lib$(TARGET).so
CURRENT_DIR = $(shell pwd)

.PHONEY = clean all test

all: lib$(TARGET).o lib$(TARGET).so

lib$(TARGET).o: $(TARGET).h $(TARGET).c
	$(CC) --std=$(CSTD) -c $(CFLAGS) -o $@ lib$(TARGET).c

lib$(TARGET).so: $(TARGET).h lib$(TARGET).c
	$(CC) --std=$(CSTD) $(CFLAGS) $(SHARED_FLAGS) -o $@ lib$(TARGET).c

test: test/lib_test test/test.sh
	bash test/test.sh

test/lib_test: lib$(TARGET).o test/testing.c
	$(CC) -o $@ --std=$(CSTD) lib$(TARGET).o ./test/testing.c

test_shared: test/test.sh test/testing.c lib$(TARGET).so
	$(CC) -o test/testing --std=$(CSTD) test/testing.c -L. -l$(TARGET)
	LD_LIBRARY_PATH=$(CURRENT_DIR);${LD_LIBRARY_PATH} bash test/test.sh

clean:
	rm -f ./test/lib_test ./test/data/test*.out *.o *.so
