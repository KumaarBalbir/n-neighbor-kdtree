# Makefile
CC = gcc
# add gdb flag (-g) for debugging
CFLAGS = -Wall -O2 -std=c11
INCLUDES = -I./src -I./utils
LDFLAGS = -lm

# Source and object files
SRC = src/main.c src/kd_tree.c utils/utils.c
OBJ = $(patsubst %.c, build/%.o, $(SRC))

# Output binary
TARGET = build/nearest_neighbor

.PHONY: all clean run dirs

all: dirs $(TARGET)

# Create build directory if it doesn't exist
dirs:
	mkdir -p build

# Build target executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

# Compile .c to .o inside build directory
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf build
