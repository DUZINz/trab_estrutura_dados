#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

// Function to create a new user
User* create_user(const char* username, const char* email) {
    User* new_user = (User*)malloc(sizeof(User));
    if (new_user == NULL) {
        fprintf(stderr, "Error allocating memory for new user.\n");
        return NULL;
    }
    strncpy(new_user->username, username, sizeof(new_user->username) - 1);
    new_user->username[sizeof(new_user->username) - 1] = '\0'; // Ensure null termination
    strncpy(new_user->email, email, sizeof(new_user->email) - 1);
    new_user->email[sizeof(new_user->email) - 1] = '\0'; // Ensure null termination
    new_user->left = NULL;
    new_user->right = NULL;
    return new_user;
}

// Function to delete a user
void delete_user(User* user) {
    if (user != NULL) {
        free(user);
    }
}

// Function to print user details
void print_user(const User* user) {
    if (user != NULL) {
        printf("Username: %s, Email: %s\n", user->username, user->email);
    }
}

// Function to compare two users for alphabetical sorting
int compare_users(const User* user1, const User* user2) {
    return strcmp(user1->username, user2->username);
}