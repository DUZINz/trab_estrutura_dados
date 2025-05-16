#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct {
    int product_code; // Novo campo para o código do produto
    char name[50];
    float price;
    int quantity;
} Product;

// se o gerenciamento for totalmente pela árvore no inventory_management)
void add_product(int product_code, const char* name, float price, int quantity);
void remove_product_by_name(const char* name); // Renomeado para clareza, se mantido
void display_products_array(); // Renomeado para clareza, se mantido

// Nova função para criar e alocar um produto (útil para a árvore)
Product* create_product(int product_code, const char* name, float price, int quantity);
void free_product(Product* product);

#endif // PRODUCT_H