CC = g++

CPPFLAGS += -Wall -Werror -MMD -MP -Isrc -g -std=c++17 

NAME = bfi

all: $(NAME)

$(NAME): main.o flags.o interpreter.o
	$(CC) $(CPPFLAGS) -o $(NAME) main.o flags.o interpreter.o

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

flags.o: ./flags/flags.cpp
	$(CC) $(CPPFLAGS) -c ./flags/flags.cpp

interpreter.o: ./interpreter/interpreter.cpp
	$(CC) $(CPPFLAGS) -c ./interpreter/interpreter.cpp
