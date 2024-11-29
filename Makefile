# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -Iinclude

# Source Files
SRCS = src/fp.c

# Object Files
OBJS = $(SRCS:.c=.o)

# Executable
TARGET = spotify

# Default Rule
all: $(TARGET)

# Linking Rule
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compilation Rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Rule
clean:
	rm -f $(OBJS) $(TARGET)

# Phony Targets
.PHONY: all clean