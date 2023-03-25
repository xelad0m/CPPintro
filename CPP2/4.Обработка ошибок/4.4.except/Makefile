CC=g++
CFLAGS=-Wall -g -std=c++11
LDFLAGS=
NAME=main

all: $(NAME)

$(NAME): $(NAME).cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	-rm $(NAME) 2>/dev/null