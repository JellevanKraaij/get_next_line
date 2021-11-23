/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:24:47 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/24 00:26:53 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_app(char **dst, const char *src, size_t srclen)
{
	size_t	dstlen;
	char	*tmp;

	dstlen = ft_strlen(*dst);
	if (dstlen + srclen == 0)
	{
		free(*dst);
		*dst = NULL;
		return (0);
	}
	tmp = malloc(srclen + dstlen + 1);
	if (tmp == NULL)
	{
		free(*dst);
		*dst = NULL;
		return (-1);
	}
	ft_memcpy(tmp, *dst, dstlen);
	ft_memcpy(tmp + dstlen, src, srclen);
	tmp[srclen + dstlen] = '\0';
	free(*dst);
	*dst = tmp;
	return (1);
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
	else
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
		if (gnl.len == 0)
			break ;
		if (ft_memchr_idx(gnl.buf, '\n', gnl.len, &gnl.nl))
		{
			if (ft_app(&gnl.ret, gnl.buf, gnl.nl + 1) < 0)
				return (free_mem(gnl.buf, gnl.ret, &left));
			if (ft_app(&left, gnl.buf + gnl.nl + 1, gnl.len - gnl.nl - 1) < 0)
				return (free_mem(gnl.buf, gnl.ret, &left));
			break ;
		}
		if (ft_app(&gnl.ret, gnl.buf, gnl.len) < 0)
			return (free_mem(gnl.buf, gnl.ret, &left));
	}
	free(gnl.buf);
	return (gnl.ret);
}
