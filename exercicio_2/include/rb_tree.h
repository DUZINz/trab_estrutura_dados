#ifndef RB_TREE_H
#define RB_TREE_H

typedef struct RBTreeNode {
    int data;
    struct RBTreeNode *left;
    struct RBTreeNode *right;
    struct RBTreeNode *parent;
    int color; // 0 for Red, 1 for Black
} RBTreeNode;

typedef struct RBTree {
    RBTreeNode *root;
    RBTreeNode *TNULL; // Sentinel node
} RBTree;

// Function prototypes
RBTree* createRBTree();
void insertRBTree(RBTree *tree, int key);
void deleteRBTree(RBTree *tree, int key);
void inorderRBTree(RBTree *tree);
RBTreeNode* searchRBTree(RBTree *tree, int key);
void freeRBTree(RBTree *tree);

#endif // RB_TREE_H