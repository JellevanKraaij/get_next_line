/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:57:31 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/02 16:52:29 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_app(char *dst, const char *src, size_t srclen)
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
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
