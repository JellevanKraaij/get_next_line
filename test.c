#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int fd1 = open("test4.txt", O_RDONLY);
	char *res;


	for (int i = 0; i < 10; i++)
	{
		res = get_next_line(fd1);
		printf("%s", res);
		free(res);
	}

	close(fd1);


	// int fd1 = open("test.txt", O_RDONLY);
	// int fd2 = open("test2.txt", O_RDONLY);
	// int fd3 = open("test3.txt", O_RDONLY);

	// char *res;

	// res = get_next_line(fd1); printf("%s\n--------------------------------------------\n", res); free(res);
	// res = get_next_line(fd2); printf("%s\n--------------------------------------------\n", res); free(res);
	// res = get_next_line(fd3); printf("%s\n--------------------------------------------\n", res); free(res);
	// res = get_next_line(fd2); printf("%s\n--------------------------------------------\n", res); free(res);
	// res = get_next_line(fd2); printf("%s\n--------------------------------------------\n", res); free(res);

	// do
	// {
	// 	res = get_next_line(fd1);
	// 	free(res);
	// } while (res != NULL);
	// do
	// {
	// 	res = get_next_line(fd2);
	// 	free(res);
	// } while (res != NULL);
	// do
	// {
	// 	res = get_next_line(fd3);
	// 	free(res);
	// } while (res != NULL);
	
	// close(fd1);
	// close(fd2);
	// close(fd3);
	while(1);
}