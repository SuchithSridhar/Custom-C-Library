CC = gcc
CFLAGS = -O3
CSTD = c18
TARGET = string

.PHONEY = clean all test

all: $(TARGET).o

$(TARGET).o: $(TARGET).h $(TARGET).c
	$(CC) --std=$(CSTD) -c $(CFLAGS) -o $(TARGET).o $(TARGET).c

test: lib_test
	./lib_test

lib_test: $(TARGET).o testing.c
	$(CC) --std=$(CSTD) -o lib_test testing.c $(TARGET).o

clean:
	rm -f ./testing
