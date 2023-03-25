CC=g++
CFLAGS=-Wall -g -std=c++11
LDFLAGS=
NAME=tuple2pair

all: $(NAME)
	-echo $(pwd)

$(NAME): $(NAME).cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	-rm $(NAME) 2>/dev/null