#include "exercicio1/include/user_management.h"
#include "exercicio1/include/user.h"
#include "exercicio1/include/avl_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static AVLTree *userTree = NULL; // Mantenha static

// Implementação de initialize_user_management
void initialize_user_management() {
    if (userTree == NULL) { // Evita múltiplas inicializações
        userTree = create_avl_tree();
    }
}

void register_user(const char *username, const char *email) { // Assinatura corrigida
    if (!userTree) {
        initialize_user_management(); // Garante inicialização
    }
    avl_insert_user(userTree, username, email); // Use a função correta da AVL
    printf("Usuário %s registrado com sucesso.\n", username);
}

void remove_user(const char *username) {
    if (!userTree) {
        fprintf(stderr, "Sistema de gerenciamento de usuários não inicializado para remover.\n");
        return;
    }
    avl_delete_user(userTree, username); // Use a função correta da AVL
    printf("Tentativa de remover usuário %s.\n", username); // Feedback
}

User* search_user(const char *username) {
    if (!userTree) {
        fprintf(stderr, "Sistema de gerenciamento de usuários não inicializado para buscar.\n");
        return NULL;
    }
    return avl_search_user(userTree, username); // Use a função correta da AVL
}

void list_users_alphabetically() {
    if (!userTree || !userTree->root) {
        printf("Nenhum usuário para listar.\n");
        return;
    }
    print_avl_users_in_order(userTree->root); // Use a função correta da AVL
}

// Implementação de cleanup_user_management
void cleanup_user_management() {
    if (userTree) {
        free_avl_tree(userTree);
        userTree = NULL;
    }
    printf("Sistema de gerenciamento de usuários finalizado.\n");
}