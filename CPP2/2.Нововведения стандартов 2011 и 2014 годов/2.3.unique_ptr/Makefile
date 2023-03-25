CC=g++
CFLAGS=-Wall -g -std=c++14
LDFLAGS=
NAME=unique_ptr

all: $(NAME)
	-echo $(pwd)

$(NAME): $(NAME).cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	-rm $(NAME) 2>/dev/null