#include "search.h"

/* print helper to match checker format */
static void print_check(const skiplist_t *node)
{
	printf("Value checked at index [%lu] = [%d]\n", node->index, node->n);
}

/* Follow express lane to determine the [start, end] block for search. */
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

/* Linear scan within [start, end] inclusive; print each comparison. */
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
 * linear_skip - search for a value in a sorted skip list (with express lane)
 * @list: pointer to head of the skip list
 * @value: value to search for
 *
 * Return: pointer to first node where value is located, or NULL
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *start, *end;

	if (list == NULL)
		return (NULL);

	find_block(list, value, &start, &end);
	return (scan_block(start, end, value));
}
