#include "rb_tree.h"
#include <stdlib.h>

typedef struct rb_node {
    int data;
    struct rb_node *left;
    struct rb_node *right;
    struct rb_node *parent;
    int color; // 0 for red, 1 for black
} rb_node;

static rb_node *root = NULL;
static rb_node *TNULL;

// Function to create a new node
rb_node* new_node(int data) {
    rb_node *node = (rb_node*)malloc(sizeof(rb_node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = 0; // New node is red
    return node;
}

// Function to perform left rotation
void left_rotate(rb_node *x) {
    rb_node *y = x->right;
    x->right = y->left;

    if (y->left != TNULL) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void right_rotate(rb_node *x) {
    rb_node *y = x->left;
    x->left = y->right;

    if (y->right != TNULL) {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

// Function to fix violations after insertion
void fix_insert(rb_node *k) {
    rb_node *u;
    while (k->parent->color == 0) {
        if (k->parent == k->parent->parent->left) {
            u = k->parent->parent->right;
            if (u->color == 0) {
                k->parent->color = 1;
                u->color = 1;
                k->parent->parent->color = 0;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    left_rotate(k);
                }
                k->parent->color = 1;
                k->parent->parent->color = 0;
                right_rotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->left;
            if (u->color == 0) {
                k->parent->color = 1;
                u->color = 1;
                k->parent->parent->color = 0;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    right_rotate(k);
                }
                k->parent->color = 1;
                k->parent->parent->color = 0;
                left_rotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = 1;
}

// Function to insert a new node
void rb_insert(int data) {
    rb_node *node = new_node(data);
    node->parent = NULL;
    node->left = TNULL;
    node->right = TNULL;

    rb_node *y = NULL;
    rb_node *x = root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == NULL) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    if (node->parent == NULL) {
        node->color = 1;
        return;
    }

    if (node->parent->parent == NULL) {
        return;
    }

    fix_insert(node);
}

// Additional functions for deletion and traversal can be implemented here.