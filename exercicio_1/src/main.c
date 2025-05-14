#include <stdio.h>
#include <stdlib.h>
#include "user_management.h"

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
    UserManagementSystem *ums = create_user_management_system();

    do {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user(ums);
                break;
            case 2:
                remove_user(ums);
                break;
            case 3:
                search_user(ums);
                break;
            case 4:
                list_users(ums);
                break;
            case 5:
                printf("Exiting the system.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    free_user_management_system(ums);
    return 0;
}