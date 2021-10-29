#include "get_next_line.h"

char	*ft_get_next_line_dup(const char *mem, size_t n)
{
	char	*dest;
	size_t	i;

	dest = malloc(n + 1);
	i = 0;
	if (dest == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = mem[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}