/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:24:47 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/12/14 17:30:49 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

static int	ft_app(char **dst, const char *src, size_t *dstlen, size_t srclen)
{
	char	*tmp;
	size_t	_dstlen;

	if (dstlen == NULL)
		_dstlen = 0;
	else
		_dstlen = *dstlen;
	if (_dstlen + srclen == 0)
	{
		free(*dst);
		return (0);
	}
	tmp = malloc(srclen + _dstlen + 1);
	if (tmp == NULL)
	{
		free(*dst);
		return (-1);
	}
	ft_memcpy(tmp, *dst, _dstlen);
	ft_memcpy(tmp + _dstlen, src, srclen);
	tmp[srclen + _dstlen] = '\0';
	free(*dst);
	*dst = tmp;
	return (1);
}

static void	*free_mem(t_gnl gnl, t_list **lst, int fd)
{
	lst_rm_fd(lst, fd);
	free(gnl.buf);
	free(gnl.ret);
	return (NULL);
}

static ssize_t	gnl_fill_buf(t_gnl *gnl, t_list **lst, int fd)
{
	char	*left;	

	if (gnl->buf == NULL)
		gnl->buf = malloc(BUFFER_SIZE);
	if (gnl->buf == NULL)
		return (-1);
	left = lst_fd_get_data(*lst, fd);
	if (left != NULL)
	{
		gnl->len = ft_strlen(left);
		ft_memcpy(gnl->buf, left, gnl->len);
		lst_rm_fd(lst, fd);
	}
	else
		gnl->len = read(fd, gnl->buf, BUFFER_SIZE);
	return (gnl->len);
}

static ssize_t	ft_memchr_idx(const void *s, int c, size_t n, size_t *res)
{
	*res = 0;
	while (*res < n)
	{
		if (((unsigned char *)s)[*res] == (unsigned char)c)
			return (*res);
		(*res)++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_gnl			gnl;
	char			*left;

	gnl.ret = NULL;
	gnl.buf = NULL;
	gnl.retlen = 0;
	while (1)
	{
		if (gnl_fill_buf(&gnl, &lst, fd) < 0)
			return (free_mem(gnl, &lst, fd));
		if (gnl.len == 0 || ft_memchr_idx(gnl.buf, '\n', gnl.len, &gnl.nl) >= 0)
			break ;
		if (ft_app(&gnl.ret, gnl.buf, &gnl.retlen, gnl.len) < 0)
			return (free_mem(gnl, &lst, fd));
		gnl.retlen += (size_t)gnl.len;
	}
	if (gnl.len > 0)
	{
		left = NULL;
		if (ft_app(&gnl.ret, gnl.buf, &gnl.retlen, gnl.nl + 1) < 0 || \
			ft_app(&left, gnl.buf + gnl.nl + 1, 0, gnl.len - gnl.nl - 1) < 0 || \
			lst_fd_update_data(&lst, fd, &left) < 0)
			return (free_mem(gnl, &lst, fd));
	}
	free(gnl.buf);
	return (gnl.ret);
}
