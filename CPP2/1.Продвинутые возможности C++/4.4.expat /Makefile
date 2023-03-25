CC=g++
CFLAGS=-Wall -g
LDFLAGS=-lexpat
NAME=expat

all: $(NAME)
	-echo $(pwd)

$(NAME): $(NAME).cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	-rm $(NAME) 2>/dev/null