#include "get_next_line.h"

size_t	get_strlen_c(const char *s, const char c)
{
	size_t	length;

	length = 0;
	while (s[length] != c)
		length++;
	return (length);
}
