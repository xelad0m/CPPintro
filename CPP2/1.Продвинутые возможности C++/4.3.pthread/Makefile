CC=g++
CFLAGS=-Wall -g -pthread -O2 
NAME=pthread

all: $(NAME)
	-echo $(pwd)

$(NAME): $(NAME).cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	-rm $(NAME) 2>/dev/null