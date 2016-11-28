CC = clang
#CFLAGS = -std=c11 -Ofast -I.
#
CFLAGS = -std=c11 -fsanitize=memory -fno-omit-frame-pointer -Weverything -O0 -g -I.
SOURCES = c8_sys.c io.c opcode.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = chirp_bin

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	-rm -f *.o core *.core
