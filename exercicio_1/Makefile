c:\Users\eduar\OneDrive\Área de Trabalho\Faculdade\trab_arv\exercicio_2
├── src
│   ├── main.c
│   ├── product.c
│   ├── rb_tree.c
│   └── inventory_management.c
├── include
│   ├── product.h
│   ├── rb_tree.h
│   └── inventory_management.h
├── Makefile
└── README.mdCC = gcc
CFLAGS = -Iinclude -Wall -Wextra
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