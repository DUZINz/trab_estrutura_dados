#include <stdio.h>
#include "exercicio2/include/inventory_management.h" // Principal header agora
#include "exercicio2/include/product.h" // Para a struct Product, se necessário diretamente

int main() {
    // Criar e inicializar o sistema de inventário
    Inventory *inventory = create_inventory();
    if (!inventory) {
        fprintf(stderr, "Falha crítica ao criar o inventário. Saindo.\n");
        return 1;
    }
    initialize_inventory_system(inventory);

    printf("\n--- Adicionando Produtos ---\n");
    add_product_to_inventory(inventory, 102, "Laptop Pro", 1200.50, 10);
    add_product_to_inventory(inventory, 101, "Mouse Gamer", 25.99, 50);
    add_product_to_inventory(inventory, 105, "Teclado Mecânico", 75.00, 30);
    add_product_to_inventory(inventory, 103, "Monitor 24pol", 150.75, 20);
    add_product_to_inventory(inventory, 104, "Webcam HD", 45.00, 15);
    add_product_to_inventory(inventory, 101, "Mouse Gamer XYZ", 27.99, 10); // Tentativa de duplicata

    printf("\n--- Exibindo Inventário Ordenado ---\n");
    display_inventory_sorted(inventory);

    printf("\n--- Buscando Produtos ---\n");
    int search_code = 103;
    Product *found = search_product_in_inventory(inventory, search_code);
    if (found) {
        printf("Produto encontrado (código %d): Nome: %s, Preço: %.2f, Qtd: %d\n",
               found->product_code, found->name, found->price, found->quantity);
    } else {
        printf("Produto com código %d não encontrado.\n", search_code);
    }

    search_code = 999;
    found = search_product_in_inventory(inventory, search_code);
    if (found) {
        printf("Produto encontrado (código %d): Nome: %s, Preço: %.2f, Qtd: %d\n",
               found->product_code, found->name, found->price, found->quantity);
    } else {
        printf("Produto com código %d não encontrado.\n", search_code);
    }

    // Exemplo de remoção (ainda é um placeholder na rb_tree.c)
    // printf("\n--- Removendo Produto (código 105) ---\n");
    // remove_product_from_inventory(inventory, 105);
    // display_inventory_sorted(inventory);


    // Limpar e sair
    cleanup_inventory_system(inventory);
    inventory = NULL; // Boa prática

    return 0;
}