CC = g++
FLAGS = -g -ggdb3
DEBAG_FLAGS = -Wall -Wextra
ASSAN = -lasan -fsanitize=address

FLAGS += $(DEBAG_FLAGS)
#FLAGS += $(ASSAN)


all: stack

function.o: stack.cpp
	$(CC) -c stack.cpp -o stack.o $(FLAGS)

main.o: main.cpp
	$(CC) -c main.cpp -o main.o $(FLAGS)

stack: stack.o main.o
	$(CC)  stack.o main.o -o stack $(FLAGS)