#include "get_next_line.h"
// #include <stdio.h>

char *get_next_line(int fd)
{
	static char	*buffer;
	static size_t	res;
	static size_t	i;

	if(i == 0)
		buffer = malloc(BUFFER_SIZE);
	if (buffer == NULL)
		return (NULL);
	if (i == 0)
		res = read(fd, buffer, BUFFER_SIZE);
	// while (1)
	// {
		// printf("res=%d, %d", res, i);
		while (i < res)
		{
			// printf("read %i-%i   ",i , buffer[i]);
			if (buffer[i] == '\n')
			{
				i += 2;
				// printf("i=%i", i);
				return (ft_get_next_line_dup(buffer, i - 1));
			}
			i++;
		}
		res = read(fd, buffer, BUFFER_SIZE);
		i = 0;
	// }
	return (NULL);
}
