/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:24:47 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/02 17:03:05 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void	addleftover(t_gnl *gnl, char **left)
{
	gnl->len = ft_strlen(*left);
	ft_memcpy(gnl->buf, *left, gnl->len + 1);
	free(*left);
	*left = NULL;
}

static char	*ft_app(char *dst, const char *src, size_t srclen)
{
	size_t	dstlen;
	char	*ret;

	dstlen = ft_strlen(dst);
	ret = malloc(srclen + dstlen + 1);
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, dst, dstlen);
	ft_memcpy(ret + dstlen, src, srclen);
	ret[srclen + dstlen] = '\0';
	free(dst);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*left;
	t_gnl		gnl;

	gnl.ret = NULL;
	if (left == NULL)
		gnl.len = read(fd, gnl.buf, BUFFER_SIZE);
	else
		addleftover(&gnl, &left);
	while (gnl.len > 0 && ft_memchr(gnl.buf, '\n', gnl.len) == NULL)
	{
		gnl.ret = ft_app(gnl.ret, gnl.buf, gnl.len);
		gnl.len = read(fd, gnl.buf, BUFFER_SIZE);
	}
	if (gnl.len < 0)
	{
		free(gnl.ret);
		return (NULL);
	}
	if (gnl.len == 0)
		return (gnl.ret);
	gnl.nl = (char *)ft_memchr(gnl.buf, '\n', gnl.len) - gnl.buf;
	gnl.ret = ft_app(gnl.ret, gnl.buf, gnl.nl + 1);
	if ((gnl.len - gnl.nl - 1) > 0)
		left = ft_app(left, gnl.nl + gnl.buf + 1, gnl.len - gnl.nl - 1);
	return (gnl.ret);
}
