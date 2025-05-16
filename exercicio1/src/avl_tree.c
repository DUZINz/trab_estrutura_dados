#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exercicio1/include/avl_tree.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(User *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

User *rightRotate(User *y) {
    User *x = y->left;
    User *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

User *leftRotate(User *x) {
    User *y = x->right;
    User *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

int getBalance(User *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

User* insert(User* node, const char* username, const char* email) {
    if (node == NULL)
        return createUser(username, email);

    if (strcmp(username, node->username) < 0)
        node->left = insert(node->left, username, email);
    else if (strcmp(username, node->username) > 0)
        node->right = insert(node->right, username, email);
    else // Duplicate usernames are not allowed
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && strcmp(username, node->left->username) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strcmp(username, node->right->username) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strcmp(username, node->left->username) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strcmp(username, node->right->username) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

User* minValueNode(User* node) {
    User* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

User* deleteNode(User* root, const char* username) {
    if (root == NULL)
        return root;

    if (strcmp(username, root->username) < 0)
        root->left = deleteNode(root->left, username);
    else if (strcmp(username, root->username) > 0)
        root->right = deleteNode(root->right, username);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            User *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            User* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            strcpy(root->username, temp->username);
            strcpy(root->email, temp->email);

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->username);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of this node to check whether this node became unbalanced
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inOrder(User *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("Username: %s, Email: %s\n", root->username, root->email);
        inOrder(root->right);
    }
}