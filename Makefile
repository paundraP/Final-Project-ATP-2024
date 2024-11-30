# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source Files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object Files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Executable
TARGET = $(BUILD_DIR)/spotify

# Default Rule
all: $(TARGET)

# Linking Rule
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(TARGET)

# Compilation Rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Rule
clean:
	rm -rf $(BUILD_DIR)

# Phony Targets
.PHONY: all clean
run:
	build/spotify