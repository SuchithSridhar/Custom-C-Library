CC = gcc
CFLAGS = -O3
CSTD = c18
TARGET = fileio

.PHONEY = clean all test

all: $(TARGET).o

$(TARGET).o: $(TARGET).h $(TARGET).c
	$(CC) --std=$(CSTD) -c $(CFLAGS) -o $(TARGET).o $(TARGET).c

test: test/testing test/test.sh
	bash test/test.sh

test/testing: $(TARGET).o test/testing.c
	$(CC) -o ./test/testing --std=$(CSTD) $(TARGET).o ./test/testing.c

clean:
	rm -f ./test/testing ./test/test*.out *.o
