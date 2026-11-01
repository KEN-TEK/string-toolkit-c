CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -g

all: demo tests

demo: main.c strtools.c strtools.h
	$(CC) $(CFLAGS) -o demo main.c strtools.c

tests: tests.c strtools.c strtools.h
	$(CC) $(CFLAGS) -o tests tests.c strtools.c

test: tests
	./tests

run: demo
	./demo

# Rebuild the tests with AddressSanitizer + UBSan to catch out-of-bounds access
check:
	$(CC) $(CFLAGS) -fsanitize=address,undefined -o tests_san tests.c strtools.c
	./tests_san
	rm -f tests_san

clean:
	rm -f demo tests tests_san

.PHONY: all test run check clean
