CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -O2 -I.

TARGET = demo
SRC = demo.c

all: $(TARGET)

$(TARGET): $(SRC) regtable.h
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
