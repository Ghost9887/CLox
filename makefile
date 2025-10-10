CC = gcc
CFLAGS = -Iinclude -O2

SRC_DIR = src
TARGET = run

SRCS = $(shell find $(SRC_DIR) -name '*.c')

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
