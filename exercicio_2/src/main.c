#include <stdio.h>
#include "product.h"
#include "rb_tree.h"
#include "inventory_management.h"

int main() {
    // Initialize the inventory management system
    initialize_inventory();

    // Example usage of product management
    add_product("Product A", 10.99);
    add_product("Product B", 5.49);
    display_products();

    // Example usage of red-black tree
    RBTree tree = create_rb_tree();
    insert_rb_tree(&tree, 15);
    insert_rb_tree(&tree, 10);
    insert_rb_tree(&tree, 20);
    printf("In-order traversal of the red-black tree:\n");
    in_order_traversal(tree);

    // Clean up and exit
    cleanup_inventory();
    return 0;
}