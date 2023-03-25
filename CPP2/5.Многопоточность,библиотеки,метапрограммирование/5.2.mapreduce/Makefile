CC=g++
CFLAGS=-Wall -g -std=c++11 -lpthread
LDFLAGS=
NAME=main

all: $(NAME)

$(NAME): $(NAME).cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	-rm $(NAME) 2>/dev/null