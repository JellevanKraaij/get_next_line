/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:24:47 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/09 15:52:07 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	ft_memchr_idx(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*_dst;

	if (src == dst)
		return (dst);
	_dst = dst;
	while (n > 0)
	{
		*(char *)dst = *(char *)src;
		dst++;
		src++;
		n--;
	}
	return (_dst);
}

static char	*ft_app(char *dst, const char *src, size_t srclen)
{
	size_t	dstlen;
	char	*ret;

	dstlen = 0;
	if (dst == NULL)
		dstlen = 0;
	else
	{
		while (dst[dstlen] != 0)
			dstlen++;
	}
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

static int	gnl_fill_buf(t_gnl *gnl, char **left, t_list **lst, int fd)
{
	gnl->ret = NULL;
	*left = lst_fd_get_data(*lst, fd);
	if (*left == NULL)
		gnl->len = read(fd, gnl->buf, BUFFER_SIZE);
	else
	{
		gnl->len = 0;
		while ((*left)[gnl->len])
			gnl->len++;
		ft_memcpy(gnl->buf, *left, gnl->len);
		*left = NULL;
		if (lst_fd_update_data(lst, fd, *left) < 0)
			return (-1);
	}
	while (gnl->len > 0 && ft_memchr_idx(gnl->buf, '\n', gnl->len) < 0)
	{
		gnl->ret = ft_app(gnl->ret, gnl->buf, gnl->len);
		gnl->len = read(fd, gnl->buf, BUFFER_SIZE);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*left;
	t_gnl			gnl;

	gnl.buf = malloc(BUFFER_SIZE);
	if (!gnl.buf || gnl_fill_buf(&gnl, &left, &lst, fd) < 0 || gnl.len < 0)
	{
		free(gnl.ret);
		free(gnl.buf);
		return (NULL);
	}
	if (gnl.len != 0)
	{
		gnl.nl = ft_memchr_idx(gnl.buf, '\n', gnl.len);
		gnl.ret = ft_app(gnl.ret, gnl.buf, gnl.nl + 1);
		if ((gnl.len - gnl.nl - 1) > 0)
			left = ft_app(left, gnl.nl + gnl.buf + 1, gnl.len - gnl.nl - 1);
		if (lst_fd_update_data(&lst, fd, left) < 0)
		{
			free(gnl.ret);
			gnl.ret = NULL;
		}
	}
	free(gnl.buf);
	return (gnl.ret);
}
