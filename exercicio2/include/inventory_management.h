#ifndef INVENTORY_MANAGEMENT_H
#define INVENTORY_MANAGEMENT_H

#include "exercicio2/include/product.h"
#include "exercicio2/include/rb_tree.h" // Para usar RBTree

typedef struct {
    RBTree *product_tree; // O inventário agora usa uma RBTree
} Inventory;

Inventory* create_inventory();
void initialize_inventory_system(Inventory *inventory); // Renomeado para evitar conflito
void add_product_to_inventory(Inventory *inventory, int product_code, const char* name, float price, int quantity);
void remove_product_from_inventory(Inventory *inventory, int product_code);
Product* search_product_in_inventory(Inventory *inventory, int product_code);
void display_inventory_sorted(Inventory *inventory);
void cleanup_inventory_system(Inventory *inventory); // Renomeado

#endif // INVENTORY_MANAGEMENT_H