

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exercicio2/include/product.h"

#define MAX_PRODUCTS 100

typedef struct {
    char name[50];
    float price;
    int quantity;
} Product;

static Product products[MAX_PRODUCTS];
static int product_count = 0;

void add_product(const char* name, float price, int quantity) {
    if (product_count < MAX_PRODUCTS) {
        strncpy(products[product_count].name, name, sizeof(products[product_count].name) - 1);
        products[product_count].name[sizeof(products[product_count].name) - 1] = '\0'; // Ensure null termination
        products[product_count].price = price;
        products[product_count].quantity = quantity;
        product_count++;
    } else {
        printf("Product list is full!\n");
    }
}

void remove_product(const char* name) {
    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].name, name) == 0) {
            products[i] = products[product_count - 1]; // Replace with last product
            product_count--;
            return;
        }
    }
    printf("Product not found!\n");
}

void display_products() {
    printf("Product List:\n");
    for (int i = 0; i < product_count; i++) {
        printf("Name: %s, Price: %.2f, Quantity: %d\n", products[i].name, products[i].price, products[i].quantity);
    }
}