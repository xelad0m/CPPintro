CC=g++
CFLAGS=-Wall -g
LDFLAGS=
NAME=namespace_search

all: $(NAME)
	-echo $(pwd)

$(NAME): $(NAME).cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	-rm $(NAME) 2>/dev/null