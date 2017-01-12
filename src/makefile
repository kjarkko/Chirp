CC = clang
#CFLAGS = -std=c11 -Ofast -I.
#gcc -std=c11 -S -O3 -masm=intel opcode.c generate assembly
GTKFLAGS = `pkg-config --cflags gtk+-3.0`
GTKLIBS = `pkg-config --libs gtk+-3.0`
CFLAGS = $(GTKFLAGS) -std=c11 -Wall -O0 -g $(GTKLIBS)
SOURCES = c8_sys.c io.c opcode.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = chirp_bin

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	-rm -f *.o core *.core *.s
