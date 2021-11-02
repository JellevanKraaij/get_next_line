#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);

	char *res;

	for(int i = 0; i < 10; i++)
	{
		printf(" - \"%s\"\n", res = get_next_line(fd));
		free(res);
	}
	close(fd);
}