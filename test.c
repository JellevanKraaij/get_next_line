#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	int fd3 = open("test3.txt", O_RDONLY);

	char *res;

	res = get_next_line(fd); printf("%s", res); free(res);
	res = get_next_line(fd2); printf("%s", res); free(res);
	res = get_next_line(fd3); printf("%s", res); free(res);
	res = get_next_line(fd2); printf("%s", res); free(res);
	res = get_next_line(fd2); printf("%s", res); free(res);

	do
	{
		res = get_next_line(fd);
		free(res);
	} while (res != NULL);
	do
	{
		res = get_next_line(fd2);
		free(res);
	} while (res != NULL);
	do
	{
		res = get_next_line(fd3);
		free(res);
	} while (res != NULL);
	
	close(fd);
	close(fd2);
	close(fd3);
}