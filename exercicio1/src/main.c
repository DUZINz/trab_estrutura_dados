#include <stdio.h>
#include <stdlib.h>
#include "exercicio1/include/user_management.h"
#include "exercicio1/include/user.h"

void display_menu() {
    printf("User Management System\n");
    printf("1. Register User\n");
    printf("2. Remove User\n");
    printf("3. Search User\n");
    printf("4. List Users Alphabetically\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int choice;
    char username_buffer[100]; // Buffer para entrada do usuário
    char email_buffer[100];    // Buffer para entrada do usuário

    initialize_user_management(); // Inicializa o sistema

    do {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Entrada inválida. Por favor, insira um número.\n");
            // Limpa o buffer de entrada em caso de falha do scanf
            while (getchar() != '\n');
            choice = -1; // Define uma escolha inválida para continuar o loop ou tratar
            continue;
        }
        // Consome o caractere de nova linha deixado pelo scanf
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choice) {
            case 1:
                printf("Digite o nome de usuário para registrar: ");
                if (fgets(username_buffer, sizeof(username_buffer), stdin) == NULL) break;
                username_buffer[strcspn(username_buffer, "\n")] = 0; // Remove a nova linha

                printf("Digite o email para registrar: ");
                if (fgets(email_buffer, sizeof(email_buffer), stdin) == NULL) break;
                email_buffer[strcspn(email_buffer, "\n")] = 0; // Remove a nova linha

                // register_user(ums); // Chamada antiga
                register_user(username_buffer, email_buffer);
                break;
            case 2:
                printf("Digite o nome de usuário para remover: ");
                if (fgets(username_buffer, sizeof(username_buffer), stdin) == NULL) break;
                username_buffer[strcspn(username_buffer, "\n")] = 0;
                // remove_user(ums); // Chamada antiga
                remove_user(username_buffer);
                break;
            case 3:
                printf("Digite o nome de usuário para buscar: ");
                if (fgets(username_buffer, sizeof(username_buffer), stdin) == NULL) break;
                username_buffer[strcspn(username_buffer, "\n")] = 0;
                // search_user(ums); // Chamada antiga
                User* found_user = search_user(username_buffer);
                if (found_user) {
                    printf("Usuário encontrado: ");
                    print_user(found_user); // Usa print_user de user.h
                } else {
                    printf("Usuário '%s' não encontrado.\n", username_buffer);
                }
                break;
            case 4:
                // list_users(ums); // Chamada antiga
                list_users_alphabetically();
                break;
            case 5:
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
        }
    } while (choice != 5);

    // free_user_management_system(ums); // Removido
    cleanup_user_management(); // Limpa os recursos
    return 0;
}