/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:24:47 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/02 21:42:50 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((char *)s);
		s++;
		n--;
	}
	return (NULL);
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
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, dst, dstlen);
	ft_memcpy(ret + dstlen, src, srclen);
	ret[srclen + dstlen] = '\0';
	free(dst);
	return (ret);
}

static int	get_next_line2(t_gnl *gnl, char **left, t_list **lst, int fd)
{
	gnl->ret = NULL;
	if (lst_fd_get_data(*lst, fd, left) < 0)
	{
		if (lst_add_f(lst, fd, NULL) < 0)
			return (-1);
	}
	if (*left == NULL)
		gnl->len = read(fd, gnl->buf, BUFFER_SIZE);
	else
	{
		gnl->len = 0;
		while ((*left)[gnl->len])
			gnl->len++;
		ft_memcpy(gnl->buf, *left, gnl->len + 1);
		free(*left);
		*left = NULL;
		lst_fd_update_data(*lst, fd, *left);
	}
	while (gnl->len > 0 && ft_memchr(gnl->buf, '\n', gnl->len) == NULL)
	{
		gnl->ret = ft_app(gnl->ret, gnl->buf, gnl->len);
		gnl->len = read(fd, gnl->buf, BUFFER_SIZE);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*left;
	t_gnl			gnl;

	if (get_next_line2(&gnl, &left, &lst, fd) < 0)
		return (NULL);
	if (gnl.len < 0)
	{
		lst_rm_fd(&lst, fd);
		free(gnl.ret);
		return (NULL);
	}
	if (gnl.len == 0)
	{
		lst_rm_fd(&lst, fd);
		return (gnl.ret);
	}
	gnl.nl = (char *)ft_memchr(gnl.buf, '\n', gnl.len) - gnl.buf;
	gnl.ret = ft_app(gnl.ret, gnl.buf, gnl.nl + 1);
	if ((gnl.len - gnl.nl - 1) > 0)
		left = ft_app(left, gnl.nl + gnl.buf + 1, gnl.len - gnl.nl - 1);
	lst_fd_update_data(lst, fd, left);
	return (gnl.ret);
}
