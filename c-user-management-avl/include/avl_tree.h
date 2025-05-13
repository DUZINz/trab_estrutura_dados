#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct User {
    char username[50];
    char email[100];
    struct User *left;
    struct User *right;
    int height;
} User;

typedef struct AVLTree {
    User *root;
} AVLTree;

// Function prototypes
AVLTree* create_avl_tree();
User* create_user(const char *username, const char *email);
User* insert_user(AVLTree *tree, User *user);
User* delete_user(AVLTree *tree, const char *username);
User* search_user(AVLTree *tree, const char *username);
void free_tree(AVLTree *tree);
void print_users_in_order(User *node);

#endif // AVL_TREE_H