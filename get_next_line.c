/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:24:47 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/10 15:51:18 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_app(char *dst, const char *src, size_t srclen)
{
	size_t	dstlen;
	char	*ret;

	dstlen = ft_strlen(dst);
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

static void	gnl_fill_buf(t_gnl *gnl, char **left, int fd)
{
	if (*left == NULL)
		gnl->len = read(fd, gnl->buf, BUFFER_SIZE);
	else
	{
		gnl->len = ft_strlen(*left);
		ft_memcpy(gnl->buf, *left, gnl->len);
		free(*left);
		*left = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*left;
	t_gnl		gnl;

	gnl.ret = NULL;
	gnl.buf = malloc(BUFFER_SIZE);
	if (gnl.buf == NULL)
		return (free_mem(gnl.buf, gnl.ret, &left));
	gnl_fill_buf(&gnl, &left, fd);
	while (gnl.len > 0 && ft_memchr_idx(gnl.buf, '\n', gnl.len) < 0)
	{
		gnl.ret = ft_app(gnl.ret, gnl.buf, gnl.len);
		gnl.len = read(fd, gnl.buf, BUFFER_SIZE);
	}
	if (gnl.len < 0)
		return (free_mem(gnl.buf, gnl.ret, &left));
	if (gnl.len != 0)
	{
		gnl.nl = ft_memchr_idx(gnl.buf, '\n', gnl.len);
		gnl.ret = ft_app(gnl.ret, gnl.buf, gnl.nl + 1);
		if ((gnl.len - gnl.nl - 1) > 0)
			left = ft_app(left, gnl.nl + gnl.buf + 1, gnl.len - gnl.nl - 1);
	}
	free(gnl.buf);
	return (gnl.ret);
}
