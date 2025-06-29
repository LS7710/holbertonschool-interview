#include "list.h"
#include <string.h>

/**
 * create_node - Creates a new List node with given string
 * @str: string to copy into node
 *
 * Return: pointer to new node or NULL on failure
 */
static List *create_node(char *str)
{
	List *node = malloc(sizeof(List));

	if (!node)
		return (NULL);

	node->str = strdup(str);
	if (!node->str)
	{
		free(node);
		return (NULL);
	}

	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/**
 * add_node_end - Adds a node to the end of a circular doubly linked list
 * @list: address of the pointer to the head
 * @str: string to store in the new node
 *
 * Return: address of the new node or NULL on failure
 */
List *add_node_end(List **list, char *str)
{
	List *new_node = create_node(str);
	List *tail;

	if (!new_node)
		return (NULL);

	if (!*list)
	{
		new_node->next = new_node;
		new_node->prev = new_node;
		*list = new_node;
	}
	else
	{
		tail = (*list)->prev;

		new_node->next = *list;
		new_node->prev = tail;
		tail->next = new_node;
		(*list)->prev = new_node;
	}

	return (new_node);
}

/**
 * add_node_begin - Adds node
 * @list: address of the pointer to the head
 * @str: string to store in the new node
 *
 * Return: address of the new node or NULL on failure
 */
List *add_node_begin(List **list, char *str)
{
	List *new_node = add_node_end(list, str);

	if (!new_node)
		return (NULL);

	*list = new_node;
	return (new_node);
}
