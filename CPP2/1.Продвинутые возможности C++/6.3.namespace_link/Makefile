CC=g++
CFLAGS=-Wall -g
LDFLAGS=
NAME=file3

all: $(NAME)
	-echo $(pwd)

$(NAME): file1.cpp file2.cpp file3.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	-rm $(NAME) 2>/dev/null