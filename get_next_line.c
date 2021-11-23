/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:24:47 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/23 20:49:21 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_app(char *dst, const char *src, size_t srclen, size_t minsize)
{
	size_t	dstlen;
	char	*ret;

	dstlen = ft_strlen(dst);
	if (srclen + dstlen + 1 <= minsize)
		ret = malloc(minsize);
	else
		ret = malloc(srclen + dstlen + 1);
	if (ret != NULL)
	{
		ft_memcpy(ret, dst, dstlen);
		ft_memcpy(ret + dstlen, src, srclen);
		ret[srclen + dstlen] = '\0';
	}
	free(dst);
	return (ret);
}

static void	*free_mem(char *buf, char *ret, char **left)
{
	free(*left);
	*left = NULL;
	free(buf);
	free(ret);
	return (NULL);
}

static ssize_t	gnl_fill_buf(t_gnl *gnl, char **left, int fd)
{
	if (*left != NULL)
	{
		gnl->len = ft_strlen(*left);
		ft_memcpy(gnl->buf, *left, gnl->len);
		free(*left);
		*left = NULL;
	}
	gnl->len = read(fd, gnl->buf, BUFFER_SIZE);
	return (gnl->len);
}

char	*get_next_line(int fd)
{
	static char	*left;
	t_gnl		gnl;

	gnl.ret = NULL;
	gnl.buf = malloc(BUFFER_SIZE);
	while (1)
	{
		if (gnl_fill_buf(&gnl, &left, fd) < 0)
			return (free_mem(gnl.buf, gnl.ret, &left));
		if (ft_memchr_idx(gnl.buf, '\n', gnl.len, &gnl.nl) || gnl.len == 0)
		{
			printf("len = %d, nl = %d\n", gnl.len, gnl.nl);
			gnl.ret = ft_app(gnl.ret, gnl.buf, gnl.nl, 0);
			if (gnl.ret != NULL && gnl.nl < gnl.len)
				left = ft_app(NULL, gnl.buf + gnl.nl + 1, gnl.len - gnl.nl - 1, 0);
			free(gnl.buf);
			return (gnl.ret);
		}
		gnl.ret = ft_app(gnl.ret, gnl.buf, gnl.len, 0);
		if (gnl.ret == NULL)
			return (free_mem(gnl.buf, gnl.ret, &left));
	}
}
