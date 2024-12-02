# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source Files
SRCS = main.c $(wildcard $(SRC_DIR)/*.c)

# Object Files
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Executable
TARGET = $(BUILD_DIR)/spotify

# Default Rule
all: $(TARGET)

# Linking Rule
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(TARGET)
	@mkdir -p playlist

# Compilation Rule for Source Files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Rule
clean:
	rm -rf $(BUILD_DIR)

# Phony Targets
.PHONY: all clean
run:
	$(TARGET)
