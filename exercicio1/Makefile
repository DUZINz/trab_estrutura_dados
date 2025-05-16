CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
SRC = src/main.c src/user.c src/avl_tree.c src/user_management.c
OBJ = $(SRC:.c=.o)
TARGET = user_management_system

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean