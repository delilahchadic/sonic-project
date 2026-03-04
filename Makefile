# 1. Compiler and Flags
CC = gcc
CFLAGS = -Wall -std=c99 -Wno-missing-braces
LDFLAGS = -lraylib # Standard Linux Raylib flags

# 2. Project Files
# This finds all your .c files automatically!
SOURCES = main.c player.c world.c camera.c sprite.c
# This turns the .c list into a .o (object) list
OBJS = $(SOURCES:.c=.o)
# The name of your final game
TARGET = sonic_game

# 3. The "Build All" Rule (The default)
all: $(TARGET)

# 4. Linking the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 5. Compiling individual .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 6. The "Clean" Rule (To start fresh)
clean:
	rm -f $(OBJS) $(TARGET)