# Makefile

CC = gcc
CFLAGS = -Wall -O2 -std=c11
INCLUDES = -I./src -I./utils
LDFLAGS = -lm

SRC = src/main.c src/point.c src/kd_tree.c utils/utils.c
OBJ = $(SRC:.c=.o)
TARGET = nearest_neighbor

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
