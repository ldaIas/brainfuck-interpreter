CC = g++

CPPFLAGS += -Wall -Werror -MMD -MP -Isrc -g -std=c++17 

NAME = bfi

all: $(NAME)

$(NAME): main.o flags.o interpreter.o
	$(CC) $(CPPFLAGS) -o $(NAME) main.o flags.o interpreter.o

main.o: ./src/main.cpp
	$(CC) $(CPPFLAGS) -c ./src/main.cpp

flags.o: ./src/flags/flags.cpp
	$(CC) $(CPPFLAGS) -c .src//flags/flags.cpp

interpreter.o: ./src/interpreter/interpreter.cpp
	$(CC) $(CPPFLAGS) -c ./src/interpreter/interpreter.cpp
