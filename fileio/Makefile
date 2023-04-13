CC = gcc
CFLAGS = -O3
CSTD = c18
TARGET = fileio

.PHONEY = clean all test

all: $(TARGET).o

$(TARGET).o: $(TARGET).h $(TARGET).c
	$(CC) --std=$(CSTD) -c $(CFLAGS) -o $(TARGET).o $(TARGET).c

test: test/testing
	./test/testing ./test/test01.in > ./test/test01.out
	@diff --color ./test/test01.exp ./test/test01.out
	@printf "\n== PASSED TEST 01\n"

test/testing: $(TARGET).o test/testing.c
	$(CC) -o ./test/testing --std=$(CSTD) $(TARGET).o ./test/testing.c

clean:
	rm -f ./test/testing ./test/test*.out *.o
