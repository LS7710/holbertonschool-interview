#include "binary_trees.h"
#include <stdlib.h>

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 *
 * @root: Double pointer to the root node of the heap
 * @value: Value to insert into the heap
 *
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
    heap_t *new_node, *parent;
    size_t size;

    if (root == NULL)
        return (NULL);

    /* Create new node */
    new_node = binary_tree_node(NULL, value);
    if (new_node == NULL)
        return (NULL);

    if (*root == NULL) /* If heap is empty, new node is root */
    {
        *root = new_node;
        return (new_node);
    }

    /* Find parent node using heap size */
    size = binary_tree_size(*root) + 1; /* Calculate position of new node */
    parent = find_parent(*root, size >> 1); /* Find parent node using level order */

    new_node->parent = parent;
    if (size & 1)
        parent->right = new_node; /* Place new node as right child */
    else
        parent->left = new_node; /* Place new node as left child */

    /* Restore Max Heap property */
    while (new_node->parent && new_node->n > new_node->parent->n)
    {
        /* Swap values */
        int temp = new_node->n;
        new_node->n = new_node->parent->n;
        new_node->parent->n = temp;

        new_node = new_node->parent;
    }

    return (new_node);
}

/**
 * binary_tree_size - Measures the size of a binary tree
 *
 * @tree: Pointer to the root node of the tree to measure
 *
 * Return: Size of the tree
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
    if (tree == NULL)
        return (0);

    return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * find_parent - Finds the parent node for insertion using size
 *
 * @root: Pointer to the root node of the heap
 * @size: Size of the heap (position where new node will be inserted)
 *
 * Return: Pointer to the parent node
 */
heap_t *find_parent(heap_t *root, size_t size)
{
    if (size == 1)
        return (root);

    if (size & 1)
        return (find_parent(root->right, size >> 1));
    else
        return (find_parent(root->left, size >> 1));
}
