# Compiler, Linker, and Assembler definitions
CC = gcc
AS = nasm

# Compilation flags
CFLAGS = -Iinclude -Wall
ASMFLAGS = -f macho64
LDFLAGS = -lraylib -framework OpenGL -framework OpenAL -framework Cocoa

# Source files
CSOURCES = $(wildcard src/c/*.c) $(wildcard src/raylib/*.c)
ASMSOURCES = $(wildcard src/asm/*.asm)
OBJECTS = $(CSOURCES:.c=.o) $(ASMSOURCES:.asm=.o)

# Target executable
TARGET = bin/game

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: src/c/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: src/asm/%.asm
	$(AS) $(ASMFLAGS) $< -o $@

%.o: src/raylib/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
