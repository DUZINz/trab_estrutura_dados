#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_management.h"
#include "avl_tree.h"
#include "user.h"

typedef struct User {
    char username[50];
    char email[100];
    struct User *left;
    struct User *right;
    int height;
} User;

AVLTree *userTree;

void initializeUserManagement() {
    userTree = createAVLTree();
}

void registerUser(const char *username, const char *email) {
    User *newUser = (User *)malloc(sizeof(User));
    strcpy(newUser->username, username);
    strcpy(newUser->email, email);
    newUser->left = newUser->right = NULL;
    newUser->height = 1;

    userTree = insertAVL(userTree, newUser);
}

void removeUser(const char *username) {
    userTree = deleteAVL(userTree, username);
}

User *searchUser(const char *username) {
    return searchAVL(userTree, username);
}

void listUsers() {
    printf("User List:\n");
    inOrderTraversal(userTree);
}