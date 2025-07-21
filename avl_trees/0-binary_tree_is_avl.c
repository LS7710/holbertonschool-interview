#include "binary_trees.h"
#include <limits.h>

/**
 * tree_height - measures the height of a binary tree
 * @tree: pointer to the root node
 * Return: height of tree, or 0 if tree is NULL
 */
static size_t tree_height(const binary_tree_t *tree)
{
	size_t left_h = 0, right_h = 0;

	if (!tree)
		return (0);
	left_h = tree_height(tree->left);
	right_h = tree_height(tree->right);
	return ((left_h > right_h ? left_h : right_h) + 1);
}

/**
 * is_bst_util - checks whether a tree is a valid BST
 *                within given exclusive bounds
 * @tree: pointer to the root node
 * @min:  lower bound (exclusive)
 * @max:  upper bound (exclusive)
 * Return: 1 if valid BST, 0 otherwise
 */
static int is_bst_util(const binary_tree_t *tree, long min, long max)
{
	if (!tree)
		return (1);
	if (tree->n <= min || tree->n >= max)
		return (0);
	return (is_bst_util(tree->left, min, tree->n) &&
		is_bst_util(tree->right, tree->n, max));
}

/**
 * check_avl - ensures each node’s subtrees differ in height ≤ 1
 * @tree: pointer to the root node
 * Return: 1 if balanced everywhere, 0 otherwise
 */
static int check_avl(const binary_tree_t *tree)
{
	int balance;

	if (!tree)
		return (1);
	balance = (int)tree_height(tree->left) -
		(int)tree_height(tree->right);
	if (balance > 1 || balance < -1)
		return (0);
	return (check_avl(tree->left) && check_avl(tree->right));
}

/**
 * binary_tree_is_avl - checks if a binary tree is a valid AVL tree
 * @tree: pointer to the root node of the tree to check
 * Return: 1 if tree is a valid AVL, 0 otherwise or if tree is NULL
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	if (!tree)
		return (0);
	if (!is_bst_util(tree, LONG_MIN, LONG_MAX))
		return (0);
	if (!check_avl(tree))
		return (0);
	return (1);
}
