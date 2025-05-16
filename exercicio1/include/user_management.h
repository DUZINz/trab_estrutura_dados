#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include "exercicio1/include/user.h"

// Função para inicializar o sistema de gerenciamento de usuários
void initialize_user_management();

void register_user(const char *username, const char *email); // Removido o parâmetro id se existia

// Função para remover um usuário por nome de usuário
void remove_user(const char *username);

// Função para buscar um usuário por nome de usuário
User* search_user(const char *username);

// Função para listar todos os usuários em ordem alfabética
void list_users_alphabetically();

// Função para limpar e liberar recursos do sistema de gerenciamento
void cleanup_user_management();

#endif // USER_MANAGEMENT_H