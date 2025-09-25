#include <stdlib.h>
#include "binary_trees.h"

/**
 * new_node - allocate and initialize a new AVL node
 * @parent: parent pointer
 * @value: integer value to store
 *
 * Return: pointer to new node, or NULL on failure
 */
static avl_t *new_node(avl_t *parent, int value)
{
	avl_t *node = malloc(sizeof(*node));

	if (!node)
		return (NULL);
	node->n = value;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/**
 * build_avl - recursively build an AVL (balanced BST) from sorted array slice
 * @array: pointer to the first element of the whole array (sorted, unique)
 * @lo:    lower index (inclusive)
 * @hi:    upper index (inclusive)
 * @parent: parent node for the subtree root (or NULL for overall root)
 *
 * Return: pointer to subtree root, or NULL on failure
 */
static avl_t *build_avl(int *array, size_t lo, size_t hi, avl_t *parent)
{
	size_t mid;
	avl_t *root;

	if (lo > hi)
		return (NULL);

	mid = lo + (hi - lo) / 2;

	root = new_node(parent, array[mid]);
	if (!root)
		return (NULL);

	root->left = build_avl(array, lo, mid ? mid - 1 : 0, root);
	if (lo < mid && !root->left)
		return (NULL);

	root->right = build_avl(array, mid + 1, hi, root);
	if (mid + 1 <= hi && !root->right)
		return (NULL);

	return (root);
}

/**
 * sorted_array_to_avl - build an AVL tree from a sorted array
 * @array: pointer to first element of sorted (strictly increasing) array
 * @size:  number of elements in @array
 *
 * Return: pointer to root of created AVL tree, or NULL on failure
 *
 * Note: By choosing the middle element as root at each step, the tree is
 *       height-balanced; no rotations are required.
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (!array || size == 0)
		return (NULL);

	return (build_avl(array, 0, size - 1, NULL));
}
