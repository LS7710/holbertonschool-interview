#include "search.h"

/**
 * print_check - Print a comparison line in the checker’s format
 * @node: pointer to node being compared
 *
 * Return: void
 */
static void print_check(const skiplist_t *node)
{
	printf("Value checked at index [%lu] = [%d]\n", node->index, node->n);
}

/**
 * find_block - Locate the candidate search range using the express lane
 * @list: pointer to head of the skip list
 * @value: value to search for
 * @start: out-param; set to start node of the block (inclusive)
 * @end: out-param; set to end node of the block (inclusive)
 *
 * Return: void
 *
 * Description:
 * Follows express pointers, printing each express check, until the first node
 * whose value is >= @value or the end of the express lane. Prints the
 * “Value found between indexes [a] and [b]” line and returns the inclusive
 * block bounds via @start and @end.
 */
static void find_block(skiplist_t *list, int value,
		       skiplist_t **start, skiplist_t **end)
{
	skiplist_t *prev = list, *cur = list->express;

	while (cur)
	{
		print_check(cur);
		if (cur->n >= value)
			break;
		prev = cur;
		cur = cur->express;
	}

	if (cur == NULL)
	{
		*end = prev;
		while ((*end)->next)
			*end = (*end)->next;
		printf("Value found between indexes [%lu] and [%lu]\n",
		       prev->index, (*end)->index);
	}
	else
	{
		printf("Value found between indexes [%lu] and [%lu]\n",
		       prev->index, cur->index);
		*end = cur;
	}
	*start = prev;
}

/**
 * scan_block - Linear scan within a bounded block [start, end]
 * @start: first node to check (inclusive)
 * @end: last node to check (inclusive)
 * @value: value to search for
 *
 * Return: pointer to the first node whose n equals @value, or NULL
 *
 * Description:
 * Iterates from @start up to @end (by index), printing each comparison in
 * the required format. Stops early and returns the node if a match is found.
 */
static skiplist_t *scan_block(skiplist_t *start, skiplist_t *end, int value)
{
	while (start && start->index <= end->index)
	{
		print_check(start);
		if (start->n == value)
			return (start);
		start = start->next;
	}
	return (NULL);
}

/**
 * linear_skip - Search for a value in a sorted skip list (with express lane)
 * @list: pointer to head of the skip list
 * @value: value to search for
 *
 * Return: pointer to the first node where value is located, or NULL
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *start, *end;

	if (list == NULL)
		return (NULL);

	find_block(list, value, &start, &end);
	return (scan_block(start, end, value));
}
