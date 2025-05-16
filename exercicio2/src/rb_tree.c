#include "exercicio2/include/rb_tree.h"
#include "exercicio2/include/product.h" // Necessário para Product
#include <stdlib.h>
#include <stdio.h> // Para impressões na travessia

// Definir a estrutura do nó aqui, pois rb_tree.h tem apenas forward declaration
struct rb_node_s {
    Product *product_data; // Alterado de int data para Product*
    struct rb_node_s *left;
    struct rb_node_s *right;
    struct rb_node_s *parent;
    int color; // 0 for red, 1 for black
};

// Funções estáticas (helpers) não precisam mais de 'static rb_node *root' ou 'static rb_node *TNULL'
// Elas receberão a árvore (RBTree* tree) como parâmetro.

// Function to create a new node
static rb_node* new_rb_node(Product *product_data, rb_node *TNULL_ptr) {
    rb_node *node = (rb_node*)malloc(sizeof(rb_node));
    if (!node) {
        perror("Failed to allocate memory for new rb_node");
        exit(EXIT_FAILURE);
    }
    node->product_data = product_data; // Armazena o ponteiro para o produto
    node->left = TNULL_ptr;
    node->right = TNULL_ptr;
    node->parent = NULL;
    node->color = 0; // New node is red
    return node;
}

void initialize_rbtree(RBTree *tree) {
    if (!tree) return;
    tree->TNULL = (rb_node*)malloc(sizeof(rb_node));
    if (!tree->TNULL) {
        perror("Failed to allocate memory for TNULL");
        exit(EXIT_FAILURE);
    }
    tree->TNULL->color = 1; // Black
    tree->TNULL->left = NULL;
    tree->TNULL->right = NULL;
    tree->TNULL->parent = NULL;
    tree->TNULL->product_data = NULL; // TNULL não tem dados de produto
    tree->root = tree->TNULL;
}

RBTree* create_rbtree() {
    RBTree *tree = (RBTree*)malloc(sizeof(RBTree));
    if (!tree) {
        perror("Failed to allocate memory for RBTree");
        exit(EXIT_FAILURE);
    }
    initialize_rbtree(tree);
    return tree;
}

// Function to perform left rotation
static void left_rotate(RBTree *tree, rb_node *x) {
    rb_node *y = x->right;
    x->right = y->left;

    if (y->left != tree->TNULL) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL) { // x era a raiz
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
static void right_rotate(RBTree *tree, rb_node *x) {
    rb_node *y = x->left;
    x->left = y->right;

    if (y->right != tree->TNULL) {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL) { // x era a raiz
        tree->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

// Function to fix violations after insertion
static void fix_insert(RBTree *tree, rb_node *k) {
    rb_node *u;
    // k->parent pode ser NULL se k for a raiz e foi inserido primeiro.
    // A cor da raiz é tratada no final de rb_insert_product.
    // O loop deve continuar enquanto k não for a raiz e o pai de k for vermelho.
    while (k != tree->root && k->parent->color == 0) {
        if (k->parent == k->parent->parent->left) {
            u = k->parent->parent->right;
            if (u->color == 0) { // Caso 1: Tio é vermelho
                k->parent->color = 1; // Preto
                u->color = 1; // Preto
                k->parent->parent->color = 0; // Vermelho
                k = k->parent->parent;
            } else { // Tio é preto
                if (k == k->parent->right) { // Caso 2: k é filho direito (triângulo)
                    k = k->parent;
                    left_rotate(tree, k);
                }
                // Caso 3: k é filho esquerdo (linha)
                k->parent->color = 1; // Preto
                k->parent->parent->color = 0; // Vermelho
                right_rotate(tree, k->parent->parent);
            }
        } else { // Simétrico ao if (pai de k é filho direito do avô de k)
            u = k->parent->parent->left;
            if (u->color == 0) { // Caso 1: Tio é vermelho
                k->parent->color = 1;
                u->color = 1;
                k->parent->parent->color = 0;
                k = k->parent->parent;
            } else { // Tio é preto
                if (k == k->parent->left) { // Caso 2: k é filho esquerdo (triângulo)
                    k = k->parent;
                    right_rotate(tree, k);
                }
                // Caso 3: k é filho direito (linha)
                k->parent->color = 1;
                k->parent->parent->color = 0;
                left_rotate(tree, k->parent->parent);
            }
        }
    }
    tree->root->color = 1; // Raiz é sempre preta
}

// Function to insert a new node
void rb_insert_product(RBTree *tree, Product *product_data) {
    if (!product_data) return; // Não insira produto nulo

    rb_node *node = new_rb_node(product_data, tree->TNULL);
    // node->parent é NULL inicialmente
    // node->left e node->right são tree->TNULL

    rb_node *y = NULL; // y será o pai do novo nó
    rb_node *x = tree->root; // x é usado para percorrer a árvore

    while (x != tree->TNULL) {
        y = x;
        if (node->product_data->product_code < x->product_data->product_code) {
            x = x->left;
        } else if (node->product_data->product_code > x->product_data->product_code) {
            x = x->right;
        } else {
            // Código de produto duplicado. Decida como lidar:
            // 1. Não inserir e liberar 'node' e 'product_data'
            // 2. Atualizar o produto existente (se permitido)
            // Por ora, vamos impedir a inserção e liberar.
            printf("Erro: Produto com código %d já existe.\n", product_data->product_code);
            free(node->product_data); // Libera o Product que não será inserido
            free(node);             // Libera o rb_node criado
            return;
        }
    }

    node->parent = y;
    if (y == NULL) { // Árvore estava vazia
        tree->root = node;
    } else if (node->product_data->product_code < y->product_data->product_code) {
        y->left = node;
    } else {
        y->right = node;
    }

    // Se o novo nó é a raiz, sua cor já é vermelha (new_rb_node),
    // mas fix_insert irá colori-lo de preto no final.
    // Se o pai é NULL, node é a raiz.
    if (node->parent == NULL) {
        node->color = 1; // Raiz é preta
        return;
    }

    // Se o avô é NULL, não há necessidade de balancear além de colorir o pai (se necessário),
    // mas a lógica de fix_insert já cobre isso.
    // O pai do novo nó (y) pode ser tree->TNULL se a árvore estava vazia,
    // mas isso é tratado por (y == NULL)
    if (node->parent == tree->TNULL) { // Isso não deveria acontecer se y foi atribuído corretamente
         node->color = 1; // Raiz é preta
         return;
    }
    
    // Só chama fix_insert se o pai do novo nó não for nulo (ou seja, não é a raiz)
    // e o pai do pai não for nulo (necessário para a lógica de tios em fix_insert)
    // A condição principal de fix_insert (k->parent->color == 0) já lida com isso.
    // Se o pai for preto, não há violação.
    if (node->parent->color == 0) { // Só precisa corrigir se o pai for vermelho
       fix_insert(tree, node);
    }
    // Garante que a raiz seja preta, fix_insert já faz isso.
    // tree->root->color = 1;
}

// Função auxiliar para busca
static rb_node* search_node_recursive(rb_node *node, int product_code, rb_node *TNULL_ptr) {
    if (node == TNULL_ptr || node->product_data == NULL) { // Adicionado node->product_data == NULL para segurança
        return NULL; // Ou TNULL_ptr se preferir indicar "não encontrado" com o sentinela
    }
    if (product_code == node->product_data->product_code) {
        return node;
    }
    if (product_code < node->product_data->product_code) {
        return search_node_recursive(node->left, product_code, TNULL_ptr);
    }
    return search_node_recursive(node->right, product_code, TNULL_ptr);
}

Product* rb_search_product(RBTree *tree, int product_code) {
    rb_node *found_node = search_node_recursive(tree->root, product_code, tree->TNULL);
    if (found_node && found_node != tree->TNULL) {
        return found_node->product_data;
    }
    return NULL;
}

// Função auxiliar para travessia in-order
static void in_order_recursive(rb_node *node, rb_node *TNULL_ptr, void (*print_product_details)(Product*, int color)) {
    if (node != TNULL_ptr) {
        in_order_recursive(node->left, TNULL_ptr, print_product_details);
        if (node->product_data) { // Verifica se product_data não é nulo
            print_product_details(node->product_data, node->color);
        }
        in_order_recursive(node->right, TNULL_ptr, print_product_details);
    }
}

void rb_in_order_traversal(RBTree *tree, void (*print_product_details)(Product*, int color)) {
    if (!print_product_details) return;
    in_order_recursive(tree->root, tree->TNULL, print_product_details);
}


// Funções de deleção (complexas, fornecendo um esqueleto e a ideia)
// transplant, fix_delete, minimum_node seriam helpers estáticos aqui.
// static rb_node* minimum_node(RBTree *tree, rb_node *node) { ... }
// static void rb_transplant(RBTree *tree, rb_node *u, rb_node *v) { ... }
// static void fix_delete(RBTree *tree, rb_node *x) { ... }

void rb_delete_product(RBTree *tree, int product_code) {
    // 1. Encontrar o nó a ser deletado (z)
    rb_node *z = search_node_recursive(tree->root, product_code, tree->TNULL);
    if (z == NULL || z == tree->TNULL) {
        printf("Produto com código %d não encontrado para remoção.\n", product_code);
        return;
    }

    Product* product_to_free = z->product_data; // Guardar para liberar depois

    // Lógica de deleção da árvore Rubro-Negra:
    rb_node *x, *y;
    int y_original_color = y->color;
    // ... (implementação completa da deleção RB) ...
    if (y_original_color == 1) { // Se o nó removido (ou seu substituto) era preto
        fix_delete(tree, x); // x é o nó que pode ter causado a violação
    }
    free(product_to_free); // Libera os dados do produto
    free(z); // Libera o nó da árvore

    printf("rb_delete_product para código %d não totalmente implementado.\n", product_code);
    // A implementação completa de fix_delete é extensa.
    // Por ora, esta função é um placeholder.
}

void free_rbtree_nodes(rb_node *node, rb_node *TNULL_ptr) {
    if (node == NULL || node == TNULL_ptr) {
        return;
    }
    free_rbtree_nodes(node->left, TNULL_ptr);
    free_rbtree_nodes(node->right, TNULL_ptr);
    if (node->product_data) {
        free(node->product_data); // Libera o produto associado
    }
    free(node); // Libera o nó
}

void destroy_rbtree(RBTree *tree) {
    if (!tree) return;
    free_rbtree_nodes(tree->root, tree->TNULL);
    if (tree->TNULL) {
        free(tree->TNULL); // Libera o nó TNULL
    }
    free(tree); // Libera a estrutura da árvore
}