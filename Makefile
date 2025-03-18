CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = tic_tac_toe.c
OBJ = $(SRC:.c=.o)
TARGET = tic_tac_toe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
