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
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

# Executable
TARGET = $(BUILD_DIR)/spotify

# Detect Architecture
ARCH := $(shell uname -m)

ifeq ($(ARCH), arm64)
CFLAGS += -march=armv8-a
else ifeq ($(ARCH), x86_64)
CFLAGS += -march=x86-64
endif

# Default Rule
all: $(TARGET)

# Linking Rule
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(TARGET)

# Compilation Rule for Source Files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Rule
clean:
	rm -rf $(BUILD_DIR)

# Phony Targets
.PHONY: all clean run

# Run Rule
run: $(TARGET)
	$(TARGET)