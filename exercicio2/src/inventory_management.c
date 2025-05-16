#include "exercicio2/include/inventory_management.h"
#include "exercicio2/include/product.h" // Para create_product
#include "exercicio2/include/rb_tree.h" // Para funções da RBTree
#include <stdio.h>
#include <stdlib.h> // Para malloc/free
#include <string.h> // Para strncpy

// Implementação de create_product e free_product (pode estar em product.c também)
Product* create_product(int product_code, const char* name, float price, int quantity) {
    Product* new_product = (Product*)malloc(sizeof(Product));
    if (!new_product) {
        perror("Failed to allocate memory for product");
        return NULL;
    }
    new_product->product_code = product_code;
    strncpy(new_product->name, name, sizeof(new_product->name) - 1);
    new_product->name[sizeof(new_product->name) - 1] = '\0';
    new_product->price = price;
    new_product->quantity = quantity;
    return new_product;
}

void free_product(Product* product) {
    if (product) {
        free(product);
    }
}


Inventory* create_inventory() {
    Inventory *inventory = (Inventory*)malloc(sizeof(Inventory));
    if (!inventory) {
        perror("Failed to create inventory");
        return NULL;
    }
    inventory->product_tree = create_rbtree(); // Cria a árvore RB
    if (!inventory->product_tree) {
        free(inventory);
        return NULL;
    }
    return inventory;
}

void initialize_inventory_system(Inventory *inventory) {
    // A inicialização da árvore (TNULL, root) é feita em create_rbtree()
    // Esta função pode ser usada para carregar dados iniciais, se necessário.
    if (inventory && inventory->product_tree) {
         printf("Sistema de inventário inicializado.\n");
    } else {
         printf("Falha ao inicializar inventário: estrutura de inventário ou árvore nula.\n");
    }
}


void add_product_to_inventory(Inventory *inventory, int product_code, const char* name, float price, int quantity) {
    if (!inventory || !inventory->product_tree) {
        printf("Erro: Inventário não inicializado.\n");
        return;
    }
    Product *new_prod = create_product(product_code, name, price, quantity);
    if (new_prod) {
        rb_insert_product(inventory->product_tree, new_prod);
        // rb_insert_product lida com a duplicação e libera new_prod se duplicado.
    } else {
        printf("Falha ao criar produto para adicionar ao inventário.\n");
    }
}

void remove_product_from_inventory(Inventory *inventory, int product_code) {
    if (!inventory || !inventory->product_tree) {
        printf("Erro: Inventário não inicializado.\n");
        return;
    }
    // A função rb_delete_product precisa ser totalmente implementada
    // e deve lidar com a liberação da memória do Product* dentro do nó removido.
    rb_delete_product(inventory->product_tree, product_code);
    printf("Tentativa de remover produto com código %d do inventário.\n", product_code);
}

Product* search_product_in_inventory(Inventory *inventory, int product_code) {
    if (!inventory || !inventory->product_tree) {
        printf("Erro: Inventário não inicializado.\n");
        return NULL;
    }
    return rb_search_product(inventory->product_tree, product_code);
}

// Função para imprimir detalhes do produto para a travessia
void print_product_details_for_inventory(Product* p, int color) {
    if (p) {
        printf("  Código: %d, Nome: %s, Preço: %.2f, Qtd: %d, Cor do Nó: %s\n",
               p->product_code, p->name, p->price, p->quantity, (color == 0 ? "Vermelho" : "Preto"));
    }
}

void display_inventory_sorted(Inventory *inventory) {
    if (!inventory || !inventory->product_tree) {
        printf("Erro: Inventário não inicializado ou vazio.\n");
        return;
    }
    printf("Inventário (ordenado por código):\n");
    rb_in_order_traversal(inventory->product_tree, print_product_details_for_inventory);
}

void cleanup_inventory_system(Inventory *inventory) {
    if (inventory) {
        if (inventory->product_tree) {
            destroy_rbtree(inventory->product_tree); // Libera a árvore e seus nós/produtos
        }
        free(inventory); // Libera a estrutura do inventário
        printf("Sistema de inventário finalizado.\n");
    }
}