#ifndef USER_H
#define USER_H

typedef struct User {
    int id; // Unique ID for the user
    char username[50]; // Name of the user
    char email[100]; // Email of the user
    struct User *left; // Left child in the AVL tree
    struct User *right; // Right child in the AVL tree
    int height; // Height of the node for AVL balancing
} User;

// Função para criar um novo usuário
User* create_user(const char* username, const char* email);

// Função para deletar a estrutura de um usuário (libera a memória)
void delete_user_struct(User* user); // Renomeada de delete_user para evitar conflitos

// Função para imprimir detalhes do usuário
void print_user(const User* user);

// Função para comparar dois usuários para ordenação alfabética
int compare_users(const User* user1, const User* user2);

#endif // USER_H