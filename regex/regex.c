#include "regex.h"

/**
 * match_here - recursive engine that matches from current positions
 * @s: current position in input string
 * @p: current position in pattern
 *
 * Return: 1 if the suffixes match, otherwise 0
 */
static int match_here(const char *s, const char *p);

/**
 * match_star - handle "c*" where c is a literal or '.'
 * @c: the element repeated by '*'
 * @p: pattern position after the "c*"
 * @s: current position in input string
 *
 * Return: 1 if a match is possible, otherwise 0
 */
static int match_star(char c, const char *p, const char *s);

/**
 * regex_match - check if an entire string matches a pattern
 * supporting '.' and '*'
 * @str: input string to test
 * @pattern: regex pattern
 *
 * Return: 1 if matches, 0 otherwise
 */
int regex_match(char const *str, char const *pattern)
{
	if (!str || !pattern)
		return (0);

	return (match_here(str, pattern));
}

static int match_here(const char *s, const char *p)
{
	/* pattern exhausted: match only if string also exhausted */
	if (*p == '\0')
		return (*s == '\0');

	/* look ahead for '*' applying to current pattern char */
	if (p[1] == '*')
		return (match_star(p[0], p + 2, s));

	/* single-character match ('.' matches any single) */
	if (*s != '\0' && (*p == '.' || *p == *s))
		return (match_here(s + 1, p + 1));

	return (0);
}

static int match_star(char c, const char *p, const char *s)
{
	/*
	 * Try all possible lengths for c* (greedy with backtracking):
	 * first try zero occurrences, then consume one-by-one while it fits.
	 */
	do {
		if (match_here(s, p))
			return (1);
		/* stop if string ended */
		if (*s == '\0')
			break;
		/* advance if next char fits 'c' (or '.' wildcard) */
		if (c == '.' || *s == c)
			s++;
		else
			break;
	} while (1);

	return (0);
}
