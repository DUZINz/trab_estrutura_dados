#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct {
    int id;
    char name[100];
    float price;
    int quantity;
} Product;

void add_product(Product *product);
void remove_product(int product_id);
void display_products();

#endif // PRODUCT_H