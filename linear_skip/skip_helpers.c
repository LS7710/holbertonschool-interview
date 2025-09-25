#include <stdio.h>
#include <stdlib.h>
#include "search.h"

/* ---- helpers count: 5 functions (3 public + 2 static) ---- */

/* floor integer sqrt without libm */
static size_t isqrt_size(size_t n)
{
	size_t r = 0;
	while ((r + 1) * (r + 1) <= n)
		r++;
	return (r);
}

/* allocate a node */
static skiplist_t *new_node(int n, size_t index)
{
	skiplist_t *node = malloc(sizeof(*node));

	if (!node)
		return (NULL);
	node->n = n;
	node->index = index;
	node->next = NULL;
	node->express = NULL;
	return (node);
}

/**
 * create_skiplist - build a skip list with express jumps every floor(sqrt(size))
 * @array: sorted values
 * @size: number of values
 * Return: head pointer or NULL
 */
skiplist_t *create_skiplist(int *array, size_t size)
{
	skiplist_t *head = NULL, *tail = NULL, *cur;
	size_t i, step, last_exp_i = 0;

	if (!array || size == 0)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		cur = new_node(array[i], i);
		if (!cur)
		{
			free_skiplist(head);
			return (NULL);
		}
		if (!head)
			head = cur, tail = cur;
		else
			tail->next = cur, tail = cur;
	}

	step = isqrt_size(size);
	if (step > 0)
	{
		skiplist_t *prev_exp = NULL, *walker = head;

		for (i = 0; walker; i++, walker = walker->next)
		{
			if (i % step == 0)
			{
				if (prev_exp)
					prev_exp->express = walker;
				prev_exp = walker;
				last_exp_i = i;
			}
		}
		(void)last_exp_i; /* silence -Wunused-variable if not used */
	}
	return (head);
}

/**
 * print_skiplist - print main list and express lane (format similar to checker)
 * @list: head
 */
void print_skiplist(const skiplist_t *list)
{
	const skiplist_t *it;

	printf("List :\n");
	for (it = list; it; it = it->next)
		printf("Index[%lu] = [%d]\n", it->index, it->n);

	printf("\nExpress lane :\n");
	if (list)
	{
		const skiplist_t *e = list;

		/* print head then follow express pointers */
		printf("Index[%lu] = [%d]\n", e->index, e->n);
		for (e = e->express; e; e = e->express)
			printf("Index[%lu] = [%d]\n", e->index, e->n);
	}
	printf("\n");
}

/**
 * free_skiplist - free all nodes (main chain)
 * @list: head
 */
void free_skiplist(skiplist_t *list)
{
	skiplist_t *tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
