#ifndef INVENTORY_MANAGEMENT_H
#define INVENTORY_MANAGEMENT_H

// Function to initialize the inventory
void initialize_inventory();

// Function to add a product to the inventory
void add_product_to_inventory(int product_id, int quantity);

// Function to remove a product from the inventory
void remove_product_from_inventory(int product_id, int quantity);

// Function to display the current inventory
void display_inventory();

// Function to check the stock of a specific product
int check_product_stock(int product_id);

#endif // INVENTORY_MANAGEMENT_H