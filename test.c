#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	printf("\n\n%s-", get_next_line(fd));
	printf("%s-", get_next_line(fd));
}