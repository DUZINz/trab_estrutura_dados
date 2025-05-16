#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "exercicio1/include/user.h"
typedef struct AVLTree {
    User *root;
} AVLTree;

AVLTree* create_avl_tree();
void avl_insert_user(AVLTree *tree, const char *username, const char *email);

void avl_delete_user(AVLTree *tree, const char *username);

User* avl_search_user(AVLTree *tree, const char *username);

void free_avl_tree(AVLTree *tree);

void print_avl_users_in_order(User *node);

#endif // AVL_TREE_H