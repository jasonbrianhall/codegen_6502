# Simple NES Makefile for cc65
PROJECT_NAME = game
TARGET = nes

# Source files
SOURCES = main.c

# Output
ROM = $(PROJECT_NAME).nes

# Build the ROM
$(ROM): $(SOURCES)
	cl65 -t $(TARGET) -o $(ROM) $(SOURCES)
	cc65 -t $(TARGET) -o main.s main.c

# Default target
all: $(ROM)

# Clean
clean:
	rm -f $(ROM) *.o *.map *.s

.PHONY: all clean
