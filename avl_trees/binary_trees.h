/* binary_trees.h */
#ifndef BINARY_TREES_H
#define BINARY_TREES_H

#include <stddef.h>

/**
 * struct binary_tree_s - Binary tree node
 *
 * @n:        Integer stored in the node
 * @parent:   Pointer to the parent node
 * @left:     Pointer to the left child node
 * @right:    Pointer to the right child node
 */
struct binary_tree_s
{
    int n;
    struct binary_tree_s *parent;
    struct binary_tree_s *left;
    struct binary_tree_s *right;
};

typedef struct binary_tree_s binary_tree_t;
typedef struct binary_tree_s avl_t;

/* Provided functions (for testing) */
binary_tree_t *binary_tree_node(binary_tree_t *parent, int n);
void binary_tree_print(const binary_tree_t *tree);

/* Task 0: check if a tree is a valid AVL */
int binary_tree_is_avl(const binary_tree_t *tree);

#endif /* BINARY_TREES_H */
