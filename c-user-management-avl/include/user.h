#ifndef USER_H
#define USER_H

typedef struct User {
    char username[50];
    char email[100];
    struct User *left;
    struct User *right;
    int height;
} User;

// Function prototypes
User* create_user(const char* username, const char* email);
void delete_user(User* user);
User* search_user(User* root, const char* username);
void list_users(User* root);

#endif // USER_H