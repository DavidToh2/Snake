# Code files to be compiled
OBJS = snake.cpp

CC = g++

COMPILER_FLAGS = -w -I/usr/include/SDL2

# Libraries that need to be linked
LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = snake.o

RM = rm -f

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	$(RM) $(OBJ_NAME)

# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
# https://stackoverflow.com/questions/7096152/c-difference-between-linking-library-and-adding-include-directories