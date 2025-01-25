#include "binary_trees.h"
#include <stdio.h>

void binary_tree_print(const binary_tree_t *tree)
{
    if (tree == NULL)
        return;

    binary_tree_print(tree->left);
    printf("%d\n", tree->n);
    binary_tree_print(tree->right);
}
