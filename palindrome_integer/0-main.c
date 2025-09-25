#include <stdlib.h>
#include <stdio.h>
#include "palindrome.h"

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on bad usage
 */
int main(int ac, char **av)
{
	unsigned long n;
	int ret;

	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s arg\n", av[0]);
		return (EXIT_FAILURE);
	}

	n = (unsigned long)atol(av[1]);
	ret = is_palindrome(n);

	printf("%lu is ", n);
	if (ret == 0)
		printf("not ");
	printf("a palindrome.\n");

	return (EXIT_SUCCESS);
}
