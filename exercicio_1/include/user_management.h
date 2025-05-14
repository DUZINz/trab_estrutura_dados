#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include "user.h"

// Function to register a new user
void register_user(User user);

// Function to remove a user by username
void remove_user(const char* username);

// Function to search for a user by username
User* search_user(const char* username);

// Function to list all users in alphabetical order
void list_users_alphabetically();

#endif // USER_MANAGEMENT_H