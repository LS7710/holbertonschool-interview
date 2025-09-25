#include <stdlib.h>
#include "binary_trees.h"

/**
 * new_node - allocate and initialize a new AVL node
 * @parent: parent pointer
 * @value: integer value
 * Return: pointer to new node or NULL
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
 * build_avl - build balanced BST (AVL by construction) from sorted slice
 * @array: sorted, unique ints
 * @lo: lower index (inclusive)
 * @hi: upper index (inclusive)
 * @parent: parent node of this subtree root
 * Return: subtree root or NULL on alloc failure
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

	/* Only recurse if there’s actually a left/right slice */
	if (mid > lo)
	{
		root->left = build_avl(array, lo, mid - 1, root);
		if (!root->left)
			return (NULL);
	}
	if (mid < hi)
	{
		root->right = build_avl(array, mid + 1, hi, root);
		if (!root->right && mid + 1 <= hi)
			return (NULL);
	}

	return (root);
}

/**
 * sorted_array_to_avl - build AVL tree from sorted array (no rotations)
 * @array: pointer to first element (sorted, unique)
 * @size: number of elements
 * Return: root pointer or NULL
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (!array || size == 0)
		return (NULL);
	return (build_avl(array, 0, size - 1, NULL));
}
