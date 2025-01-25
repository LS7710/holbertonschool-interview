#include "binary_trees.h"
#include <stdio.h>

/**
 * binary_tree_print - Prints a binary tree
 * @tree: Pointer to the root node of the tree
 */
void binary_tree_print(const binary_tree_t *tree)
{
    if (tree == NULL)
        return;

    /* Inorder traversal */
    binary_tree_print(tree->left);
    printf("%d\n", tree->n);
    binary_tree_print(tree->right);
}
