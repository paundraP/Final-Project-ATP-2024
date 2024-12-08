CC = gcc

CFLAGS = -Wall -Wextra -Iinclude -static
LDFLAGS = -lmpg123 -lm

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
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@mkdir -p playlists
	@mkdir -p songs

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ 


clean:
	rm -rf $(BUILD_DIR)
	rm -rf songs

.PHONY: all clean run

run: $(TARGET)
	$(TARGET)
