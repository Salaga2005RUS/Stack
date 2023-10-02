CC = g++
FLAGS = -g -ggdb3
DEBUG_FLAGS = -Wall -Wextra -D_DEBUG
ASSAN = -lasan -fsanitize=address
# /home/gr1nd3/.local/bin/colour-valgrind

FLAGS += $(DEBUG_FLAGS)
FLAGS += $(ASSAN)


all: stack

function.o: stack.cpp
	$(CC) -c stack.cpp -o stack.o $(FLAGS)

main.o: main.cpp
	$(CC) -c main.cpp -o main.o $(FLAGS)

stack: stack.o main.o
	$(CC)  stack.o main.o -o stack $(FLAGS)