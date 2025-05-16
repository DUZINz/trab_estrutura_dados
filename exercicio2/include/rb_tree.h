#ifndef RB_TREE_H
#define RB_TREE_H
#include "exercicio2/include/product.h" 

// Forward declaration para evitar dependência circular se rb_node fosse definido aqui
typedef struct rb_node_s rb_node;

typedef struct {
    rb_node *root;
    rb_node *TNULL;
} RBTree;

// Funções de gerenciamento da árvore
RBTree* create_rbtree();
void initialize_rbtree(RBTree *tree); // Para inicializar TNULL e root
void rb_insert_product(RBTree *tree, Product *product_data);
Product* rb_search_product(RBTree *tree, int product_code);
void rb_delete_product(RBTree *tree, int product_code); // Esqueleto/Implementação
void rb_in_order_traversal(RBTree *tree, void (*print_product_details)(Product*, int color));
void free_rbtree_nodes(rb_node *node, rb_node *TNULL_ptr); // Função auxiliar para liberar memória
void destroy_rbtree(RBTree *tree); // Libera TNULL e chama free_rbtree_nodes

#endif // RB_TREE_H