CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

SRCS = main.c $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

TARGET = $(BUILD_DIR)/spotify

ARCH := $(shell uname -m)

ifeq ($(ARCH), arm64)
CFLAGS += -march=armv8-a
else ifeq ($(ARCH), x86_64)
CFLAGS += -march=x86-64
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(TARGET)
	@mkdir -p playlist

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run

run: $(TARGET)
	$(TARGET)