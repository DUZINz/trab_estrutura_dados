CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = src/main.c src/product.c src/rb_tree.c src/inventory_management.c
OBJ = $(SRC:.c=.o)
TARGET = inventory_management_system

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean