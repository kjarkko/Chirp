CC = clang
CFLAGS = -std=c11 -Ofast -o prog -I.
CFLAGS_DEBUG = -std=c11 -Weverything -O0 -g -I.
SOURCES = c8_sys.c io.c opcode.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = chirp_bin

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS_DEBUG) -o $@ $^

.PHONY: clean

clean:
	-rm -f *.o core *.core
