#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	char *str;
	int fd = open("test.txt", O_RDONLY);
	int i = 0;

	printf("fd=%d",fd);
	while((str = get_next_line(fd)) != NULL && i < 10)
	{
		printf("%s", str);
		i++;
	}
	return (1);
}