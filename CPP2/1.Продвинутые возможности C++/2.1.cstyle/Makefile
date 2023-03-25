CC=g++
CFLAGS=-Wall -g
NAME=cstyle

all: $(NAME)
	-echo $(pwd)

$(NAME): $(NAME).cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	-rm $(NAME) 2>/dev/null